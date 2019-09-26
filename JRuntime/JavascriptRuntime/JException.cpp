#include "stdafx.h"
#include "Globals.h"
#include "JException.h"

JsValueRef JException::Internal::callback;
bool JException::Internal::isRegisterd;
PVOID JException::Internal::nativeHandlerHandle;


JException::Internal::JsException::JsException(PEXCEPTION_POINTERS exception)
{
	auto exceptionInfo = exception->ExceptionRecord->ExceptionInformation;

	Thrower = (int)exception->ExceptionRecord->ExceptionAddress;
	Type = TranslateExceptionType(exception->ExceptionRecord->ExceptionCode);

	Operation = TranslateOperation(exceptionInfo[0]);
	Target= exceptionInfo[1];
}

std::string JException::Internal::JsException::TranslateOperation(unsigned long operation)
{
	switch (operation)
	{
	case 0:
		return "Read";
	case 1:
		return "Write";
	case 8:
		return "DEP";
	default:
		return "Unknown";
	}
}

std::string JException::Internal::JsException::TranslateExceptionType(int code)
{
	switch (code)
	{
	case EXCEPTION_ACCESS_VIOLATION:
		return "ACCESS_VIOLATION";
	case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
		return "ARRAY_BOUNDS_EXCEEDED";
	case EXCEPTION_BREAKPOINT:
		return "BREAKPOINT";
	case EXCEPTION_DATATYPE_MISALIGNMENT:
		return "DATATYPE_MISALIGNMENT";
	case EXCEPTION_FLT_DENORMAL_OPERAND:
		return "FLT_DENORMAL_OPERAND";
	case EXCEPTION_FLT_DIVIDE_BY_ZERO:
		return "FLT_DIVIDE_BY_ZERO";
	case EXCEPTION_FLT_INEXACT_RESULT:
		return "FLT_INEXACT_RESULT";
	case EXCEPTION_FLT_INVALID_OPERATION:
		return "FLT_INVALID_OPERATION";
	case EXCEPTION_FLT_OVERFLOW:
		return "FLT_OVERFLOW";
	case EXCEPTION_FLT_STACK_CHECK:
		return "FLT_STACK_CHECK";
	case EXCEPTION_FLT_UNDERFLOW:
		return "FLT_UNDERFLOW";
	case EXCEPTION_ILLEGAL_INSTRUCTION:
		return "ILLEGAL_INSTRUCTION";
	case EXCEPTION_IN_PAGE_ERROR:
		return "IN_PAGE_ERROR";
	case EXCEPTION_INT_DIVIDE_BY_ZERO:
		return "INT_DIVIDE_BY_ZERO";
	case EXCEPTION_INT_OVERFLOW:
		return "INT_OVERFLOW";
	case EXCEPTION_INVALID_DISPOSITION:
		return "INVALID_DISPOSITION";
	case EXCEPTION_NONCONTINUABLE_EXCEPTION:
		return "NONCONTINUABLE_EXCEPTION";
	case EXCEPTION_PRIV_INSTRUCTION:
		return "PRIV_INSTRUCTION";
	case EXCEPTION_SINGLE_STEP:
		return "SINGLE_STEP";
	case EXCEPTION_STACK_OVERFLOW:
		return "STACK_OVERFLOW";
	default:
		return "UNKNOWN";
	}
}





void JException::AddHandler(JsValueRef handler)
{
	Internal::callback = handler;
	Internal::nativeHandlerHandle = AddVectoredExceptionHandler(1, JException::Internal::NativeExceptionHandler);
	Internal::isRegisterd = true;
}

void JException::RemoveHandler()
{
	if(Internal::isRegisterd)
		RemoveVectoredExceptionHandler(Internal::nativeHandlerHandle);
}


long __stdcall JException::Internal::NativeExceptionHandler(PEXCEPTION_POINTERS exception)
{
	Globals::JavascriptRuntime->SetCurrentContext();

	JsValueRef undefined;
	JsGetUndefinedValue(&undefined);
	std::vector<JsValueRef> params;
	params.push_back(undefined);

	JObject jException("exception");

	JsException jsException(exception);

	jException.AttachProperty(JProperty("location", Globals::ValueParser->ToJsValue<int>(jsException.Thrower)));
	jException.AttachProperty(JProperty("address", Globals::ValueParser->ToJsValue<int>(jsException.Target)));
	jException.AttachProperty(JProperty("operation", Globals::ValueParser->ToJsValue<std::string>(jsException.Operation)));
	jException.AttachProperty(JProperty("type", Globals::ValueParser->ToJsValue<std::string>(jsException.Type)));

	params.push_back(jException.Value);

	JsCallFunction(Internal::callback, params.data(), params.size(), 0);

	Globals::JavascriptRuntime->DisposeContext();

	return EXCEPTION_CONTINUE_EXECUTION;
}

