#include "stdafx.h"
#include "Disassembler.h"

Disassembler::Disassembler(cs_arch arch, cs_mode mode)
{
	this->arch = arch;
	this->mode = mode;
}

std::vector<cs_insn> Disassembler::GetInstructions(int adress, int minimumTotalSizeInBytes)
{
	csh handle;
	cs_open(arch, mode, &handle);
	cs_insn* insn = cs_malloc(handle);
	const uint8_t* code = (uint8_t*)adress;
	size_t maxInstructionSize = 15;

	uint64_t x = 0x000;
	std::vector<cs_insn> instructions;

	while (cs_disasm_iter(handle, &code, &maxInstructionSize, &x, insn))
	{
		instructions.push_back(*insn);

		if (GetTotalInstructionLength(instructions) >= minimumTotalSizeInBytes)
			break;
	}
	
	return instructions;
}

int Disassembler::GetTotalInstructionLength(std::vector<cs_insn> instructions)
{
	int totalSize = 0;

	for (auto i : instructions)
		totalSize += i.size;

	return totalSize;
}
