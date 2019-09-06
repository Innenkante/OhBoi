#include "stdafx.h"
#include "Globals.h"
#include "JException.h"

JsValueRef JException::Internal::callback;
bool JException::Internal::isRegisterd;
PVOID JException::Internal::nativeHandlerHandle;

void JException::AddHandler(JsValueRef handler)
{
	Internal::callback = handler;
	Internal::nativeHandlerHandle = AddVectoredExceptionHandler(0, (PVECTORED_EXCEPTION_HANDLER)Internal::NativeExceptionHandler);
	Internal::isRegisterd = true;
}

void JException::RemoveHandler()
{
	RemoveVectoredExceptionHandler(Internal::nativeHandlerHandle);
}

long __stdcall JException::Internal::NativeExceptionHandler(_EXCEPTION_POINTERS exception)
{
	Globals::JavascriptRuntime->SetCurrentContext();

	JsValueRef undefined;
	JsGetUndefinedValue(&undefined);
	std::vector<JsValueRef> params;
	params.push_back(undefined);

	JObject jException("exception");

	if (exception.ExceptionRecord->ExceptionCode == EXCEPTION_ACCESS_VIOLATION)
	{
		return 0;
	}

	jException.AttachProperty(JProperty("address", Globals::ValueParser->ToJsValue<int>((int)exception.ExceptionRecord->ExceptionAddress)));
	jException.AttachProperty(JProperty("code", Globals::ValueParser->ToJsValue<int>((int)exception.ExceptionRecord->ExceptionCode)));

	params.push_back(jException.Value);

	JsCallFunction(Internal::callback, params.data(), params.size(), 0);

	Globals::JavascriptRuntime->DisposeContext();
	return EXCEPTION_CONTINUE_EXECUTION;
}
