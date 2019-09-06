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
	void PlaceShellcodeHook(int adress, std::string shellcode);
	void PlaceCallbackHook(int adress, JCallback* callback);
	void PlaceManualCallbackHook(int address, JManualCallback* callback);
private:
	int GetOverrideableInstructionLength(int adress);
	std::string PrepareCallbackShellcode(JCallback * callback);
};