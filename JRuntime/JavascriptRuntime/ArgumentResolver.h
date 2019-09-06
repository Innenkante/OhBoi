#pragma once
#include <string>
#include <vector>
#include "ChakraCore.h"
#include "Globals.h"

class ArgumentResolver
{
public:
	ArgumentResolver(std::string argFormat);
	std::vector<JsValueRef> ResolveArgsToJsVector(int* arguments);
	std::vector<int> ResolveArgsToIntArray(JsValueRef * array, int* result);
	JsValueRef ResolveReturnValueToJsValue(int* value);

	static int GetArgCount(std::string format);
private:
	std::string format;
	std::vector<std::string> GetArgTypes();

	std::string GetArgType();

	JsValueRef TranslateArgToJsValue(std::string typeAsString, int * param);
	std::tuple<int,int> TranslateJsValueToArgument(std::string typeAsString, JsValueRef param);

	static std::string delemiter;
};
