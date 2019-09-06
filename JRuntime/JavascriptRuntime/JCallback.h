#pragma once
#include <ChakraCommon.h>
#include <map>
#include <vector>
#include <functional>
#include <string>
class JCallback
{
public:
	typedef void (*__stdcall JCallbackHandler)(int argCount, int* format, int* params, JsValueRef callback);
	JsValueRef JCallbackAdress;
	int ParameterCount;
	char* Format;
	int* Parameters;

	JCallbackHandler Handler;

	JCallback(int argCount, const char* format, JsValueRef callback, JCallbackHandler handler);
	
	

private:

};
