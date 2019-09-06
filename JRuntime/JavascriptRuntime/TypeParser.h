#pragma once
#include "ChakraCore.h"
#include "TypeParsers.h"
#include <map>
#include <typeinfo>
#include <typeindex>
#include <functional>




class TypeParser
{
public:
	TypeParser();
	template<class T>
	T ToType(JsValueRef jsValue);
	template<class T>
	JsValueRef ToJsValue(T value);

private:
	std::map<std::type_index, void*> parser;

};

template<class T>
inline T TypeParser::ToType(JsValueRef jsValue)
{
	return ((BaseParser<T>*)parser[std::type_index(typeid(T))])->ToType(jsValue);
}

template<class T>
inline JsValueRef TypeParser::ToJsValue(T value)
{
	return ((BaseParser<T>*)parser[std::type_index(typeid(T))])->ToJsValue(value);
}