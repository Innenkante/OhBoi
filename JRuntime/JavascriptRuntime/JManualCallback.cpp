#include "stdafx.h"
#include "JManualCallback.h"

JManualCallback::JManualCallback(const char * prologue, const char * epilogue, JsValueRef callback, JManualCallbackHandler handler)
{
	Prologue = new char[strlen(prologue) + 1];
	sprintf_s(Prologue, strlen(prologue) + 1, "%s", prologue);
	Epilogue = new char[strlen(epilogue) + 1];
	sprintf_s(Epilogue, strlen(epilogue) + 1, "%s", epilogue);
	Callback = callback;
	ManualCallbackHandler = handler;
}
