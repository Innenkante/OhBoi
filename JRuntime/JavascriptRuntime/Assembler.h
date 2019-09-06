#pragma once
#include <string>
#include "keystone.h"
#include <vector>

class Assembler
{
public:
	Assembler(ks_arch arch,ks_mode mode);
	std::vector<unsigned char> Assemble(std::string instructions);
	static void CreateJump(unsigned char * source, unsigned char * destination);
	static void CreateCall(unsigned char* source, unsigned char* functionToCall);
	static DWORD SetProtection(int adress, int length, DWORD protection);
	static void Nop(unsigned char * adress, int offset, int length);
private:
	ks_arch architecture;
	ks_mode mode;
};

