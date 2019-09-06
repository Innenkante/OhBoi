#include "stdafx.h"
#include "Hook.h"

void Hook::PlaceShellcodeHook(int adress, std::string shellcode)
{
	auto compiler = Assembler(KS_ARCH_X86, KS_MODE_32);
	auto code = compiler.Assemble(shellcode);

	auto instructionLength = GetOverrideableInstructionLength(adress);

	DWORD old = Assembler::SetProtection(adress, instructionLength, PAGE_EXECUTE_READWRITE);

	unsigned char* destination = (unsigned char*)VirtualAlloc(0, 1024, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	unsigned char* source = (unsigned char*)adress;

	memcpy(destination, code.data(), code.size()); //our code

	memcpy(destination + code.size(), source, instructionLength); //original code

	Assembler::CreateJump(destination + instructionLength + code.size(), source + instructionLength);
	Assembler::CreateJump(source, destination);

	Assembler::Nop(source, 5, instructionLength);

	Assembler::SetProtection(adress, instructionLength, old);
}

void Hook::PlaceCallbackHook(int adress, JCallback* callback)
{

	auto shellcode = PrepareCallbackShellcode(callback);

	auto assembler = Assembler(KS_ARCH_X86, KS_MODE_32);

	auto code = assembler.Assemble(shellcode);

	auto instructionLength = GetOverrideableInstructionLength(adress);

	DWORD old = Assembler::SetProtection(adress, instructionLength, PAGE_EXECUTE_READWRITE);

	unsigned char* destination = (unsigned char*)VirtualAlloc(0, 1024, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	unsigned char* source = (unsigned char*)adress;

	memcpy(destination, code.data(), code.size()); //our code without the jump

	Assembler::CreateCall(destination + code.size(), (unsigned char*)callback->Handler); //jump to the callbackHandler

	memcpy(destination + code.size() + 5, source, instructionLength); //copy original code + 5 for the call to the callback

	Assembler::CreateJump(destination + instructionLength + code.size() + 5, source + instructionLength); //jump back the original code after our code, the copied code and 5 more bytes for the call to the callback
	Assembler::CreateJump(source, destination);

	Assembler::Nop(source, 5, instructionLength);

	Assembler::SetProtection(adress, instructionLength, old);

	//NOTE: It fucking works.
}

void Hook::PlaceManualCallbackHook(int address, JManualCallback * callback)
{
	auto assembler = Assembler(KS_ARCH_X86, KS_MODE_32);

	auto prologue = assembler.Assemble(callback->Prologue);
	auto argumentSetup = assembler.Assemble("push " + std::to_string((int)callback->Callback) + ";");
	auto epilogue = assembler.Assemble(callback->Epilogue);

	auto allocatedMemory = (unsigned char*)VirtualAlloc(0, 1024, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	unsigned char* source = (unsigned char*)address;

	int overridableInstructions = GetOverrideableInstructionLength(address);

	auto old = Assembler::SetProtection(address, overridableInstructions, PAGE_EXECUTE_READWRITE);

	memcpy(allocatedMemory, prologue.data(), prologue.size());
	memcpy(allocatedMemory + prologue.size(), argumentSetup.data(), argumentSetup.size());
	Assembler::CreateCall(allocatedMemory + prologue.size() + argumentSetup.size(), (unsigned char*)callback->ManualCallbackHandler);
	memcpy(allocatedMemory + prologue.size() + argumentSetup.size() + 0x5, epilogue.data(), epilogue.size());
	Assembler::CreateJump(allocatedMemory + prologue.size() + argumentSetup.size() + 0x5 + epilogue.size(), source + overridableInstructions);


	Assembler::CreateJump(source, allocatedMemory);
	Assembler::Nop(source, 5, overridableInstructions);

	Assembler::SetProtection(address, overridableInstructions, old);
}

int Hook::GetOverrideableInstructionLength(int adress)
{
	auto disassembler = Disassembler(CS_ARCH_X86, CS_MODE_32);

	auto instructions = disassembler.GetInstructions(adress, 5);
	return disassembler.GetTotalInstructionLength(instructions);
}

std::string Hook::PrepareCallbackShellcode(JCallback* callback)
{
	/*
	Seems like that esp + 4 holds the first param
	therefore if we push eax, the first param is located at esp+8
	afterwards, if we pop eax;, the first param is at esp+4 again
	*/

	std::string shellcode = "push eax;";

	for (int i = 0; i < callback->ParameterCount; i++)
	{
		shellcode += "mov eax, [esp + " + std::to_string((i + 2) * 4) + "]; mov [" + std::to_string((int)(callback->Parameters + i * 4)) + "], eax;";
	}

	shellcode += "pop eax;";

	shellcode += "push " + std::to_string((int)callback->JCallbackAdress) + ";";
	shellcode += "push " + std::to_string((int)&(callback->Parameters[0])) + ";";
	shellcode += "push " + std::to_string((int)&(callback->Format[0])) + ";";
	shellcode += "push " + std::to_string(callback->ParameterCount) + ";";


	return shellcode;
}



