#include <ChakraCommon.h>

class JException
{
public:
	static void AddHandler(JsValueRef handler);
	static void RemoveHandler();

	int Thrower;
	int Target;
	std::string Operation;
	std::string Type;

private:
	std::string TranslateOperation(unsigned long operation);
	std::string TranslateExceptionType(int code);
	JException(PEXCEPTION_POINTERS exception);


	static JsValueRef callback;
	static bool isHandlerRegistered;
	static HANDLE exceptionHandler;
	static long __stdcall NativeExceptionHandler(PEXCEPTION_POINTERS exception);
};

