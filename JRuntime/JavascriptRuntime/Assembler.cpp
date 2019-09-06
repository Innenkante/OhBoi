#include "stdafx.h"
#include "Assembler.h"

Assembler::Assembler(ks_arch arch, ks_mode mode)
{
	architecture = arch;
	this->mode = mode;
}

std::vector<unsigned char> Assembler::Assemble(std::string instructions)
{
	ks_engine* keystoneEngine;
	unsigned char* compiledInstructions;
	size_t numberOfBytes;
	size_t offsets;

	ks_open(architecture, mode, &keystoneEngine);
	auto error = ks_asm(keystoneEngine, instructions.c_str(), 0, &compiledInstructions, &numberOfBytes, &offsets);
	ks_close(keystoneEngine);
	
	auto result = std::vector<unsigned char>();
	result.assign(compiledInstructions, compiledInstructions + numberOfBytes);

	return result;
}

void Assembler::CreateJump(unsigned char * source, unsigned char * destination)
{
	auto jmpDestination = (int)destination - (int)source - 0x5;

	source[0] = 0xE9;
	*(int*)(source + 1) = jmpDestination;
}

void Assembler::CreateCall(unsigned char* source, unsigned char* functionToCall)
{
	auto callDestination = (int)functionToCall - (int)source - 0x5;

	source[0] = 0xE8;
	*(int*)(source + 1) = callDestination;
}


DWORD Assembler::SetProtection(int adress, int length, DWORD protection)
{
	DWORD old = 0;
	VirtualProtect((int*)adress, length, protection, &old);

	return old;
}

void Assembler::Nop(unsigned char* adress, int offset, int length)
{
	for (int i = offset; i < length; i++)
		adress[i] = 0x90;
}