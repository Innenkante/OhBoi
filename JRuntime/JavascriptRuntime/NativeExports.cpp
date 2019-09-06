#include "stdafx.h"
#include "NativeExports.h"
#include "JExports.h"

JExport void LoadJavascriptFile(char* file)
{
	Globals::JavascriptRuntime->InitializeContext();
	JExports::Initialize();
	std::string fileAsString(file);
	Globals::JavascriptRuntime->LoadScript(std::wstring(fileAsString.begin(),fileAsString.end()).c_str());
	Globals::JavascriptRuntime->RunScript();
	//MessageBoxA(NULL, std::to_string(Globals::ValueParser->ToType<int>(Globals::JavascriptRuntime->GetResult())).c_str(), "Result!", 0);
}

JExport void UnloadJavascriptFile(char* file)
{
	Globals::JavascriptRuntime->UnloadCurrentScript();
}
