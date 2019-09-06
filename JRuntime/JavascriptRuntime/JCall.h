#pragma once
#include <map>

class JCall
{
public:
	typedef void(*__stdcall ParameterLessTrampoline)();
	enum CallingConvention
	{
		Stdcall = 0,
		Cdecl = 1,
		Thiscall = 2
	};

	int Address;
	int ArgCount;
	CallingConvention Convention;
	char* Format;
	char* ReturnFormat;
	int* Arguments;
	int* ReturnValue;
	ParameterLessTrampoline Trampoline;


	JCall(int address, int argCount, CallingConvention convention, const char* returnFormat, const char* format);

	void Call(int* arguments);

	static void InitializeJCall(JCall* call);
	static void AddFunctionCall(JCall* call);
	static JCall* GetFunctionCall(int adress);
	static bool ExistsFunctionCall(int adress);
private:
	static std::map<int, JCall*> calls;
};