#pragma once
#include <string>
#include "ChakraCore.h"
class JBaseType
{
public:
	std::string Name;
	JsValueRef Id;
	JsValueRef Value;
	JBaseType(const std::string &name, JsValueRef value)
	{
		Name = name;
		Value = value;
	}
	JBaseType() {}
protected:
	bool AlreadyExists(JBaseType jBaseType)
	{
		bool exists;
		JsGetPropertyIdFromName(std::wstring(Name.begin(), Name.end()).c_str(), &Id);
		JsHasProperty(Value, Id, &exists);

		return exists;
	}
};

class JProperty : public JBaseType
{
public:
	JProperty(const std::string &name, JsValueRef value) : JBaseType(name, value) {}
};

class JFunction : public JBaseType
{
public:
	JFunction(const std::string &name, JsValueRef value) : JBaseType(name, value) {}
	JFunction(const std::string &name, JsNativeFunction function)
	{
		Name = name;
		JsCreateFunction(function, nullptr, &Value);
	}
};

class JObject : public JBaseType
{
public:
	JObject(const std::string &name, JsValueRef value) : JBaseType(name, value) {}
	JObject(const std::string name)
	{
		Name = name;
		JsCreateObject(&Value);
	}

	void AttachObject(JObject jObject)
	{
		auto error1 = JsCreatePropertyId(jObject.Name.c_str(), jObject.Name.length(), &jObject.Id);
		auto error2 = JsSetProperty(Value, jObject.Id, jObject.Value, true);
	}


	void AttachProperty(JProperty prop)
	{
		auto error1 = JsCreatePropertyId(prop.Name.c_str(), prop.Name.length(), &prop.Id);
		auto error2 = JsSetProperty(Value, prop.Id, prop.Value, true);
	}

	void AttachFunction(JFunction function)
	{
		auto error1 = JsCreatePropertyId(function.Name.c_str(), function.Name.length(), &function.Id);
		auto error2 = JsSetProperty(Value, function.Id, function.Value, true);
	}

	JsValueRef GetPropertyValueFromName(std::string name)
	{
		std::wstring wName = std::wstring(name.begin(), name.end());

		JsValueRef tempId = 0;
		JsValueRef tempValue;
		auto error1 = JsGetPropertyIdFromName(wName.c_str(), &tempId);
		auto error2 = JsGetProperty(Value, tempId, &tempValue);

		return tempValue;
	}

};
