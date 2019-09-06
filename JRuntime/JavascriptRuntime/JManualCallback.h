#pragma once
#include <ChakraCommon.h>
#include <stdio.h>

class JManualCallback
{
public:
	typedef void(*__stdcall JManualCallbackHandler)(JsValueRef callback);
	char* Prologue;
	char* Epilogue;
	JsValueRef Callback;

	JManualCallbackHandler ManualCallbackHandler;

	JManualCallback(const char* prologue, const char* epilogue, JsValueRef callback, JManualCallbackHandler handler);



private:

};
