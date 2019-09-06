#include "stdafx.h"
#include "JCallback.h"

JCallback::JCallback(int argCount, const char* format, JsValueRef callback, JCallbackHandler handler)
{
	ParameterCount = argCount;
	Format = new char[strlen(format) + 1];
	sprintf_s(Format, strlen(format) + 1, "%s", format);
	Parameters = new int[argCount];
	JCallbackAdress = callback;
	Handler = handler;
}

