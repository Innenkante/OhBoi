#pragma once
#include "ChakraCore.h"
#include <string>
#include <sstream>
#include <fstream>
#include "JTypes.h"

class JRuntime
{
public:
	JRuntime();
	void InitializeContext();
	void DisposeContext();
	void SetCurrentContext();
	void LoadScript(const std::wstring& path);
	void RunScript();
	void UnloadCurrentScript();
	JsValueRef GetResult();
	JObject GetGlobalObject();
	JsValueRef GetCurrentContext();

private:
	std::wstring scriptCode;
	JsRuntimeHandle runtime;
	JsContextRef context;
	unsigned sourceContext;
	JsValueRef scriptReturnValue;
};
