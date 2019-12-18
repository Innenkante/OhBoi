#include "stdafx.h"
#include "JRuntime.h"
#include "Globals.h"

JRuntime::JRuntime()
{
	JsCreateRuntime(JsRuntimeAttributeNone, nullptr, &runtime);
}



void JRuntime::InitializeContext()
{
	JsCreateContext(runtime, &context);
}

void JRuntime::DisposeContext()
{
	auto error = JsSetCurrentContext(nullptr);
}

void JRuntime::SetCurrentContext()
{
	JsSetCurrentContext(nullptr);
	auto error = JsSetCurrentContext(context);
}

void JRuntime::LoadScript(const std::wstring & path)
{
	std::wifstream file(path);
	std::wstringstream fileStream;
	fileStream << file.rdbuf();
	scriptCode = fileStream.str();
	scriptCode.insert(0, L"(function() {");
	scriptCode.insert(scriptCode.length(), L"})();");
}

void JRuntime::RunScript()
{
	SetCurrentContext();
	auto error = JsRunScript(scriptCode.c_str(), sourceContext, L"", &scriptReturnValue);
	if (error)
	{
		JsValueRef exception, lineNumberRef;
		JsGetAndClearException(&exception);

		JsPropertyIdRef lineNumber, columnNumber;

		JsGetPropertyIdFromName(L"line", &lineNumber);

		JsGetProperty(exception, lineNumber, &lineNumberRef);

		auto text = Globals::ValueParser->ToType<std::string>(exception);
		MessageBoxA(NULL, (text + "on line: " + std::to_string(Globals::ValueParser->ToType<int>(lineNumberRef))).c_str(), "Exception", 0);

		DisposeContext();
	}

	DisposeContext(); //if we don't, we can't move the context trough threads
}

void JRuntime::UnloadCurrentScript()
{
	DisposeContext();
	InitializeContext();
	scriptCode.clear();
}

JsValueRef JRuntime::GetResult()
{
	return scriptReturnValue;
}

JObject JRuntime::GetGlobalObject()
{
	SetCurrentContext();
	JsValueRef tmp;
	JsGetGlobalObject(&tmp);

	return JObject("", tmp);
}

JsValueRef JRuntime::GetCurrentContext()
{
	return context;
}
