#include "stdafx.h"
#include "JCall.h"
#include "Assembler.h"

#include <string>



std::map<int, JCall*> JCall::calls;


JCall::JCall(int address, int argCount, CallingConvention convention, const char* returnFormat, const char * format)
{
	Address = address;
	ArgCount = argCount;
	Convention = convention;
	ReturnFormat = new char[strlen(returnFormat) + 1];
	Format = new char[strlen(format) + 1];
	Arguments = new int[argCount];
	ReturnValue = new int;

	sprintf_s(ReturnFormat, strlen(returnFormat) + 1, "%s", returnFormat);
	sprintf_s(Format, strlen(format) + 1, "%s", format);
}

void JCall::Call(int * arguments)
{
	for (int i = 0; i < ArgCount; i++)
		Arguments[i] = arguments[i];

	Trampoline();
}


void JCall::InitializeJCall(JCall* call)
{
	std::string argumentShellcode;
	std::string cleanupShellcode;

	auto allocatedSpace = VirtualAlloc(0, 1024, MEM_COMMIT, PAGE_EXECUTE_READWRITE);

	for (int i = call->ArgCount; i > 0; i--)
	{
		int address = (int)call->Arguments + (i - 1) * 4;
		int address2 = (int)&(call->Arguments[i - 1]);

		argumentShellcode += "push [" + std::to_string(address) + "];";
	}

	if(call->Convention == JCall::CallingConvention::Stdcall)
		cleanupShellcode = "mov [" + std::to_string((int)call->ReturnValue) + "], eax; ret;";

	if (call->Convention == JCall::CallingConvention::Cdecl)
		cleanupShellcode = "mov [" + std::to_string((int)call->ReturnValue) + "], eax; add esp, " + std::to_string(call->ArgCount * 4) + "; ret;";

	auto assembler = Assembler(KS_ARCH_X86, KS_MODE_32);

	auto argumentSetup = assembler.Assemble(argumentShellcode);
	auto cleanupSetup = assembler.Assemble(cleanupShellcode);

	memcpy(allocatedSpace, argumentSetup.data(), argumentSetup.size());

	Assembler::CreateCall(((unsigned char*)allocatedSpace) + argumentSetup.size(), (unsigned char*)call->Address);

	memcpy((unsigned char*)allocatedSpace + argumentSetup.size() + 5, cleanupSetup.data(), cleanupSetup.size());

	call->Trampoline = (ParameterLessTrampoline)allocatedSpace;
}

void JCall::AddFunctionCall(JCall * call)
{
	calls.insert(std::pair<int, JCall*>(call->Address, call));
}

JCall * JCall::GetFunctionCall(int adress)
{
	return calls[adress];
}

bool JCall::ExistsFunctionCall(int adress)
{
	if (calls.count(adress) == 0)
		return false;
	return true;
}


