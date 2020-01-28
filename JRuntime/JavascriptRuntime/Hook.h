#pragma once
#include <functional>
#include "string"
#include "Assembler.h"
#include "Disassembler.h"
#include "JCallback.h"
#include "JManualCallback.h"

class Hook
{
public:
	bool PlaceShellcodeHook(int adress, std::string shellcode);
	void PlaceCallbackHook(int adress, JCallback* callback);
	bool PlaceManualCallbackHook(int address, JManualCallback* callback);
private:
	int GetOverrideableInstructionLength(int adress);
	std::string PrepareCallbackShellcode(JCallback * callback);
};