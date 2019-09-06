#include "stdafx.h"
#include "ArgumentResolver.h"
#include "Globals.h"
#include <iostream>
#include <sstream>
#include<tuple>

#include "Resource.h"

std::string ArgumentResolver::delemiter = ",";








ArgumentResolver::ArgumentResolver(std::string argFormat)
{
	format = argFormat;
}

std::vector<JsValueRef> ArgumentResolver::ResolveArgsToJsVector(int * arguments)
{
	auto types = GetArgTypes();
	std::vector<JsValueRef> result;

	for (int i = 0; i < types.size(); i++)
		result.push_back(TranslateArgToJsValue(types[i], arguments + i * 4));

	return result;
}

std::vector<int> ArgumentResolver::ResolveArgsToIntArray(JsValueRef * array, int * result)
{
	auto types = GetArgTypes();
	std::vector<int> resourceIndexes;

	for (int i = 0; i < types.size(); i++)
	{
		auto tuple = TranslateJsValueToArgument(types[i], array[i + 1]); //as arguments[0] references to the this pointer

		if (std::get<0>(tuple) != -1)
			resourceIndexes.push_back(std::get<0>(tuple));

		result[i] = std::get<1>(tuple);
	}

	return resourceIndexes;
}

JsValueRef ArgumentResolver::ResolveReturnValueToJsValue(int * value)
{
	std::string type = GetArgType();
	return TranslateArgToJsValue(type, value);
}


int ArgumentResolver::GetArgCount(std::string format)
{
	std::istringstream stream(format);
	std::string subString;

	if (format == "none")
		return 0;

	if (format.find(delemiter) == std::string::npos)
	{
		return 1;
	}


	int paramCount = 0;
	while (std::getline(stream, subString, delemiter.c_str()[0]))
	{
		paramCount++;
	}

	return paramCount;
}

std::vector<std::string> ArgumentResolver::GetArgTypes()
{
	std::istringstream stream(format);

	std::vector<std::string> paramTypes;
	std::string subString;

	if (format == "none")
		return std::vector<std::string>(); //so it does not loop trough it as there is nothing to parse

	if (format.find(delemiter) == std::string::npos)
	{
		paramTypes.push_back(format);
		return paramTypes;
	}

	while (std::getline(stream, subString, delemiter.c_str()[0]))
	{
		paramTypes.push_back(subString);
	}

	return paramTypes;

}

std::string ArgumentResolver::GetArgType()
{
	std::istringstream stream(format);

	std::vector<std::string> paramTypes;
	std::string subString;

	if (format.find(delemiter) == std::string::npos)
	{
		paramTypes.push_back(format);
		return paramTypes[0];
	}

	while (std::getline(stream, subString, delemiter.c_str()[0]))
	{
		paramTypes.push_back(subString);
	}

	return paramTypes[0];
}

JsValueRef ArgumentResolver::TranslateArgToJsValue(std::string type, int * param)
{
	if (type == "int")
	{
		return Globals::ValueParser->ToJsValue<int>((int)*param);
	}
	if (type == "float")
	{
		return Globals::ValueParser->ToJsValue<float>((float)*param);
	}
	if (type == "double")
	{
		return Globals::ValueParser->ToJsValue<double>((double)*param);
	}
	if (type == "bool")
	{
		return Globals::ValueParser->ToJsValue<bool>((bool)*param);
	}
	if (type == "string")
	{
		if (HIWORD((int*)(*param)) == 0)
			return Globals::ValueParser->ToJsValue<int>((int)(int*)*param); //if they pass an ordinal instead of the string

		return Globals::ValueParser->ToJsValue<std::string>((char*)*param);
	}
	if (type == "wstring")
	{
		if (HIWORD((int*)(*param)) == 0)
			return Globals::ValueParser->ToJsValue<int>((int)(int*)*param); //if they pass an ordinal instead of the wstring


		std::wstring wString((wchar_t*)*param);
		return Globals::ValueParser->ToJsValue<std::string>(std::string(wString.begin(), wString.end()));
	}

	if (format == "none")
	{
		return Globals::ValueParser->ToJsValue<int>(0);
	}

}

std::tuple<int, int> ArgumentResolver::TranslateJsValueToArgument(std::string type, JsValueRef param)
{

	if (type == "int")
	{
		return std::make_tuple(-1, Globals::ValueParser->ToType<int>(param));
	}
	if (type == "float")
	{
		return std::make_tuple(-1, Globals::ValueParser->ToType<float>(param));
	}
	if (type == "double")
	{
		return std::make_tuple(-1, Globals::ValueParser->ToType<double>(param));
	}
	if (type == "bool")
	{
		return std::make_tuple(-1, Globals::ValueParser->ToType<bool>(param));
	}
	if (type == "string")
	{
		auto string = Globals::ValueParser->ToType<std::string>(param);
		char* buffer = new char[strlen(string.data()) + 1];
		sprintf_s(buffer, strlen(string.data()) + 1, "%s", string.data());

		int index = Resource::AddResource(Resource(buffer));

		return std::make_tuple(index, (int)buffer);
	}
	if (type == "wstring")
	{
		auto string = Globals::ValueParser->ToType<std::string>(param);
		auto wstring = std::wstring(string.begin(), string.end());

		wchar_t* wBuffer = new wchar_t[wcslen(wstring.data() + 1)];
		swprintf_s(wBuffer, wcslen(wstring.data() + 1), L"%s", wstring.data());

		int index = Resource::AddResource(Resource(wBuffer));

		return std::make_tuple(index, (int)wBuffer);
	}

	if (type == "intArray")
	{
		auto arr = Globals::ArrayParser->ToType<int>(param);
		int* ints = new int[arr.size()];
		memcpy(ints, arr.data(), arr.size());

		int index = Resource::AddResource(Resource(ints));

		return std::make_tuple(index, (int)ints);
	}
	if (type == "floatArray")
	{
		auto arr = Globals::ArrayParser->ToType<float>(param);
		float* floats = new float[arr.size()];
		memcpy(floats, arr.data(), arr.size());

		int index = Resource::AddResource(Resource(floats));

		return std::make_tuple(index, (int)floats);
	}




	if (format == "none")
	{
		return std::make_tuple(-1, 0);
	}
}
