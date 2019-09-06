#pragma once
#include "ChakraCore.h"
#include "PEBParser.h"
#include <string>

template<class T>
class BaseParser
{
protected:
	T Value;
	JsValueRef JsValue;

public:
	virtual T ToType(JsValueRef jsValue) = 0;
	virtual JsValueRef ToJsValue(T value) = 0;
};

class IntParser : BaseParser<int>
{
public:
	 int ToType(JsValueRef jsValue)
	{
		JsValueRef tmp;
		JsConvertValueToNumber(jsValue, &tmp);
		JsNumberToInt(tmp, &Value);

		return Value;
	}
	JsValueRef ToJsValue(int value)
	{
		JsIntToNumber(value, &JsValue);

		return JsValue;
	}
};

class DoubleParser : BaseParser<double>
{
	double ToType(JsValueRef jsValue)
	{
		JsValueRef tmp;
		JsConvertValueToNumber(jsValue, &tmp);
		JsNumberToDouble(tmp, &Value);

		return Value;
	}
	JsValueRef ToJsValue(double value)
	{
		JsDoubleToNumber(value, &JsValue);
		
		return JsValue;
	}
};

class StringParser : BaseParser<std::string>
{
	std::string ToType(JsValueRef jsValue)
	{
		JsValueRef tmp;
		JsConvertValueToString(jsValue, &tmp);

		size_t length;
		JsCopyString(tmp, nullptr, 0, &length);
		char* nativeString = new char[length + 1];
		JsCopyString(tmp, nativeString, length + 1, nullptr);

		nativeString[length] = '\0'; //escaping the string properly

		Value = std::string(nativeString);

		delete[] nativeString;

		return Value;
	}
	JsValueRef ToJsValue(std::string value)
	{
		std::wstring tmp = std::wstring(value.begin(), value.end());
		JsPointerToString(tmp.c_str(), tmp.length(), &JsValue);

		return JsValue;
	}

};

class BoolParser : BaseParser<bool>
{
public:
	bool ToType(JsValueRef jsValue)
	{
		JsValueRef tmp;
		JsConvertValueToBoolean(jsValue, &tmp);
		JsBooleanToBool(tmp, &Value);

		return Value;
	}
	JsValueRef ToJsValue(bool value)
	{
		JsBoolToBoolean(value, &JsValue);

		return JsValue;
	}
};

class FloatParser : BaseParser<float>
{
public:
	float ToType(JsValueRef jsValue)
	{
		JsValueRef tmp;
		double tmpValue;
		JsConvertValueToNumber(jsValue, &tmp);
		JsNumberToDouble(tmp, &tmpValue);

		Value = (float)tmpValue;

		return Value;
	}
	JsValueRef ToJsValue(float value)
	{
		JsDoubleToNumber((double)value, &JsValue);

		return JsValue;
	}
};