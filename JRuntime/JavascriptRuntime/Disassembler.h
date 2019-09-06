#pragma once
#include "capstone.h"
#include <vector>

class Disassembler
{
public:
	Disassembler(cs_arch arch, cs_mode mode);
	std::vector<cs_insn> GetInstructions(int adress, int minimumTotalSizeInBytes);
	int GetTotalInstructionLength(std::vector<cs_insn> instructions);
private:
	cs_arch arch;
	cs_mode mode;
};