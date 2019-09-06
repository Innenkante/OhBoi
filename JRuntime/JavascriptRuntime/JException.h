#include <ChakraCommon.h>

namespace JException
{
	namespace Internal
	{
		extern JsValueRef callback;
		extern bool isRegisterd;
		extern void* nativeHandlerHandle;
		extern long __stdcall NativeExceptionHandler(_EXCEPTION_POINTERS exception);
	}


	void AddHandler(JsValueRef handler);
	void RemoveHandler();

}
