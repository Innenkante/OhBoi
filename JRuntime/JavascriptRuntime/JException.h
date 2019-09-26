#include <ChakraCommon.h>

namespace JException
{
	namespace Internal
	{
		extern JsValueRef callback;
		extern bool isRegisterd;
		extern void* nativeHandlerHandle;
		extern long __stdcall NativeExceptionHandler(PEXCEPTION_POINTERS exception);

		class JsException
		{
		public:
			JsException(PEXCEPTION_POINTERS exception);

			int Thrower;
			int Target;
			std::string Operation;
			std::string Type;

		private:
			std::string TranslateOperation(unsigned long operation);
			std::string TranslateExceptionType(int code);
		};
		
	}


	void AddHandler(JsValueRef handler);
	void RemoveHandler();
}
