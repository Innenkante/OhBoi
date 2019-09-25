#pragma once
#include <vector>

#include "Globals.h"
#include "ChakraCommon.h"

class CollectionParser
{
public:
	CollectionParser() {}
	template<class T>
	std::vector<T> ToType(JsValueRef jsValue);
	template<class T>
	JsValueRef ToJsValue(std::vector<T> value);
};

template<class T>
inline std::vector<T> CollectionParser::ToType(JsValueRef jsValue)
{
	JsPropertyIdRef propertyId;
	JsValueRef jsLength;

	JsGetPropertyIdFromName(L"length", &propertyId);
	JsGetProperty(jsValue, propertyId, &jsLength);

	int length = Globals::ValueParser->ToType<int>(jsLength);

	std::vector<T> result;

	JsValueRef element;
	
	for (int i = 0; i < length; i++)
	{
		JsGetIndexedProperty(jsValue, Globals::ValueParser->ToJsValue<int>(i), &element);
		result.push_back(Globals::ValueParser->ToType<T>(element));
	}

	return result;
}

template<class T>
inline JsValueRef CollectionParser::ToJsValue(std::vector<T> value)
{
	JsValueRef jsArray;
	JsCreateArray(value.size(), &jsArray);

	for (int i = 0; i < value.size(); i++)
	{
		JsSetIndexedProperty(jsArray, Globals::ValueParser->ToJsValue<int>(i), Globals::ValueParser->ToJsValue<T>(value[i]));
	}

	return jsArray;
}
