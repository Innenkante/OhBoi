#pragma once
#include <iostream>
#include <algorithm>
#include <string>

#include "Globals.h"
#include "JTypes.h"
#include "PEBParser.h"
#include "Assembler.h"
#include "Disassembler.h"
#include "Hook.h"
#include "ArgumentResolver.h"
#include "JCall.h"
#include "JManualCallback.h"
#include "Resource.h"
#include "JException.h"


namespace JExports
{
	namespace JConsole
	{
		JsValueRef CALLBACK JAllocConsole(JsValueRef callee, bool isConstructCall, JsValueRef* arguments, unsigned short argCount, void* callbackState)
		{
			AllocConsole();
			FILE* out;
			freopen_s(&out, "CONOUT$", "w", stdout);

			return 0;

		}

		JsValueRef CALLBACK JFreeConsole(JsValueRef callee, bool isConstructCall, JsValueRef* arguments, unsigned short argCount, void* callbackState)
		{
			FreeConsole();

			return 0;
		}

		JsValueRef CALLBACK JSetConsoleTitle(JsValueRef callee, bool isConstructCall, JsValueRef* arguments, unsigned short argCount, void* callbackState)
		{
			SetConsoleTitleA(Globals::ValueParser->ToType<std::string>(arguments[1]).c_str());

			return 0;
		}


		JsValueRef CALLBACK JLog(JsValueRef callee, bool isConstructCall, JsValueRef* arguments, unsigned short argCount, void* callbackState)
		{
			std::cout << Globals::ValueParser->ToType<std::string>(arguments[1]).c_str() << std::endl;

			return 0;
		}
	}

	namespace JMemory
	{
		JsValueRef CALLBACK JReadInt(JsValueRef callee, bool isConstructCall, JsValueRef* arguments, unsigned short argCount, void* callbackState)
		{
			auto result = *(int*)(Globals::ValueParser->ToType<int>(arguments[1]));
			return Globals::ValueParser->ToJsValue<int>(result);
		}

		JsValueRef CALLBACK JWriteInt(JsValueRef callee, bool isConstructCall, JsValueRef* arguments, unsigned short argCount, void* callbackState)
		{
			*(int*)(Globals::ValueParser->ToType<int>(arguments[1])) = Globals::ValueParser->ToType<int>(arguments[2]);
			return 0;
		}

		JsValueRef CALLBACK JReadBool(JsValueRef callee, bool isConstructCall, JsValueRef* arguments, unsigned short argCount, void* callbackState)
		{
			auto result = *(bool*)(Globals::ValueParser->ToType<int>(arguments[1]));
			return Globals::ValueParser->ToJsValue<bool>(result);
		}

		JsValueRef CALLBACK JWriteBool(JsValueRef callee, bool isConstructCall, JsValueRef* arguments, unsigned short argCount, void* callbackState)
		{
			*(bool*)(Globals::ValueParser->ToType<int>(arguments[1])) = Globals::ValueParser->ToType<bool>(arguments[2]);
			return 0;
		}

		JsValueRef CALLBACK JReadString(JsValueRef callee, bool isConstructCall, JsValueRef* arguments, unsigned short argCount, void* callbackState)
		{
			std::string result((char*)Globals::ValueParser->ToType<int>(arguments[1]));
			return Globals::ValueParser->ToJsValue<std::string>(result);
		}

		JsValueRef CALLBACK JWriteString(JsValueRef callee, bool isConstructCall, JsValueRef* arguments, unsigned short argCount, void* callbackState)
		{
			auto string = Globals::ValueParser->ToType<std::string>(arguments[2]);
			memcpy((void*)(Globals::ValueParser->ToType<int>(arguments[1])), string.data(), string.length());
			return 0;
		}

		JsValueRef CALLBACK JReadFloat(JsValueRef callee, bool isConstructCall, JsValueRef* arguments, unsigned short argCount, void* callbackState)
		{
			auto result = *(float*)(Globals::ValueParser->ToType<int>(arguments[1]));
			return Globals::ValueParser->ToJsValue<float>(result);
		}

		JsValueRef CALLBACK JWriteFloat(JsValueRef callee, bool isConstructCall, JsValueRef* arguments, unsigned short argCount, void* callbackState)
		{
			*(float*)(Globals::ValueParser->ToType<int>(arguments[1])) = Globals::ValueParser->ToType<float>(arguments[2]);
			return 0;
		}

		JsValueRef CALLBACK JReadDouble(JsValueRef callee, bool isConstructCall, JsValueRef* arguments, unsigned short argCount, void* callbackState)
		{
			auto result = *(double*)(Globals::ValueParser->ToType<int>(arguments[1]));
			return Globals::ValueParser->ToJsValue<double>(result);
		}

		JsValueRef CALLBACK JWriteDouble(JsValueRef callee, bool isConstructCall, JsValueRef* arguments, unsigned short argCount, void* callbackState)
		{
			*(double*)(Globals::ValueParser->ToType<int>(arguments[1])) = Globals::ValueParser->ToType<double>(arguments[2]);
			return 0;
		}

		JsValueRef CALLBACK JWriteIntArray(JsValueRef callee, bool isConstructCall, JsValueRef* arguments, unsigned short argCount, void* callbackState)
		{
			auto address = Globals::ValueParser->ToType<int>(arguments[1]);
			auto arr = Globals::ArrayParser->ToType<int>(arguments[2]);
			memcpy((int*)address, arr.data(), arr.size() * sizeof(int));
			return 0;
		}

		JsValueRef CALLBACK JWriteFloatArray(JsValueRef callee, bool isConstructCall, JsValueRef* arguments, unsigned short argCount, void* callbackState)
		{
			auto address = Globals::ValueParser->ToType<int>(arguments[1]);
			auto arr = Globals::ArrayParser->ToType<float>(arguments[2]);
			memcpy((int*)address, arr.data(), arr.size() * sizeof(float));
			return 0;
		}

		JsValueRef CALLBACK JWriteBoolArray(JsValueRef callee, bool isConstructCall, JsValueRef* arguments, unsigned short argCount, void* callbackState)
		{
			auto address = (bool*)Globals::ValueParser->ToType<int>(arguments[1]);
			auto arr = Globals::ArrayParser->ToType<bool>(arguments[2]);

			for (int i = 0; i < arr.size();i++)
			{
				*(address + i * sizeof(bool)) = arr[i];
			}

			return 0;
		}

		JsValueRef CALLBACK JWriteDoubleArray(JsValueRef callee, bool isConstructCall, JsValueRef* arguments, unsigned short argCount, void* callbackState)
		{
			auto address = Globals::ValueParser->ToType<int>(arguments[1]);
			auto arr = Globals::ArrayParser->ToType<double>(arguments[2]);
			memcpy((int*)address, arr.data(), arr.size() * sizeof(double));
			return 0;
		}








		JsValueRef CALLBACK JVirtualAlloc(JsValueRef callee, bool isConstructCall, JsValueRef* arguments, unsigned short argCount, void* callbackState)
		{
			void* result = VirtualAlloc(0, Globals::ValueParser->ToType<int>(arguments[1]), MEM_COMMIT, PAGE_EXECUTE_READWRITE);

			auto adress = (int)result;

			return Globals::ValueParser->ToJsValue(adress);
		}

		JsValueRef CALLBACK JVirtualFree(JsValueRef callee, bool isConstructCall, JsValueRef* arguments, unsigned short argCount, void* callbackState)
		{
			VirtualFree((void*)Globals::ValueParser->ToType<int>(arguments[1]), Globals::ValueParser->ToType<int>(arguments[2]), MEM_RELEASE);

			return 0;
		}

		JsValueRef CALLBACK JVirtualProtect(JsValueRef callee, bool isConstructCall, JsValueRef* arguments, unsigned short argCount, void* callbackState)
		{
			DWORD oldprotection;
			VirtualProtect((void*)Globals::ValueParser->ToType<int>(arguments[1]), Globals::ValueParser->ToType<int>(arguments[3]), Globals::ValueParser->ToType<int>(arguments[2]), &oldprotection);

			return 0;
		}

		JsValueRef CALLBACK JVirtualQuery(JsValueRef callee, bool isConstructCall, JsValueRef* arguments, unsigned short argCount, void* callbackState)
		{
			MEMORY_BASIC_INFORMATION basicInfo;

			VirtualQuery((void*)Globals::ValueParser->ToType<int>(arguments[1]), &basicInfo, sizeof(MEMORY_BASIC_INFORMATION));

			return Globals::ValueParser->ToJsValue<int>(basicInfo.Protect);
		}

	}

	namespace JWinApi
	{
		JsValueRef CALLBACK JGetModules(JsValueRef callee, bool isConstructCall, JsValueRef* arguments, unsigned short argCount, void* callbackState)
		{
			auto modules = PEBParser().GetModules();

			JsValueRef jsArray;
			JsCreateArray(modules.size(), &jsArray);
			
			
			for (int i = 0; i < modules.size(); i++)
			{
				auto module = modules[i];
				JObject jModule("module");
				
				jModule.AttachProperty(JProperty("name", Globals::ValueParser->ToJsValue<std::string>(module.Name)));
				jModule.AttachProperty(JProperty("path", Globals::ValueParser->ToJsValue<std::string>(module.Path)));
				jModule.AttachProperty(JProperty("address", Globals::ValueParser->ToJsValue<int>(module.DllBase)));

				JsSetIndexedProperty(jsArray, Globals::ValueParser->ToJsValue<int>(i), jModule.Value);

			}

			return jsArray;
		}

		JsValueRef CALLBACK JGetModule(JsValueRef callee, bool isConstructCall, JsValueRef* arguments, unsigned short argCount, void* callbackState)
		{
			auto modules = PEBParser().GetModules();

			auto moduleName = Globals::ValueParser->ToType<std::string>(arguments[1]);

			JObject jModule("module");

			for (auto m : modules)
			{
				if (m.Name == moduleName)
				{

					jModule.AttachProperty(JProperty("name", Globals::ValueParser->ToJsValue<std::string>(m.Name)));
					jModule.AttachProperty(JProperty("path", Globals::ValueParser->ToJsValue<std::string>(m.Path)));
					jModule.AttachProperty(JProperty("address", Globals::ValueParser->ToJsValue<int>(m.DllBase)));

					return jModule.Value;
				}
			}

			jModule.AttachProperty(JProperty("name", Globals::ValueParser->ToJsValue<std::string>("Not found")));
			jModule.AttachProperty(JProperty("path", Globals::ValueParser->ToJsValue<std::string>("Not found")));
			jModule.AttachProperty(JProperty("address", Globals::ValueParser->ToJsValue<int>(0x0000)));

			return jModule.Value;
		}
		
		JsValueRef CALLBACK JGetExports(JsValueRef callee, bool isConstructCall, JsValueRef* arguments, unsigned short argCount, void* callbackState)
		{
			auto modules = PEBParser().GetModules();

			auto moduleName = Globals::ValueParser->ToType<std::string>(arguments[1]);

			for (auto m : modules)
			{
				if (m.Name == moduleName)
				{
					auto exports = m.GetExports();

					JsValueRef jsArray;
					JsCreateArray(modules.size(), &jsArray);

					for (int i = 0; i < exports.size(); i++)
					{
						JObject jExport("export");
						auto e = exports[i];
						jExport.AttachProperty(JProperty("name", Globals::ValueParser->ToJsValue<std::string>(e.Name)));
						jExport.AttachProperty(JProperty("address", Globals::ValueParser->ToJsValue<int>(e.Adress)));

						JsSetIndexedProperty(jsArray, Globals::ValueParser->ToJsValue<int>(i), jExport.Value);
					}

					return jsArray;
				}
			}

			JsValueRef jsArray;
			JsCreateArray(modules.size(), &jsArray);

			JObject jExport("export");
			jExport.AttachProperty(JProperty("name", Globals::ValueParser->ToJsValue<std::string>("Not found")));
			jExport.AttachProperty(JProperty("address", Globals::ValueParser->ToJsValue<int>(0x0000)));

			JsSetIndexedProperty(jsArray, 0, jExport.Value);
			
			return jsArray;
		}

		JsValueRef CALLBACK JGetExport(JsValueRef callee, bool isConstructCall, JsValueRef* arguments, unsigned short argCount, void* callbackState)
		{
			auto modules = PEBParser().GetModules();

			auto moduleName = Globals::ValueParser->ToType<std::string>(arguments[1]);
			auto functionName = Globals::ValueParser->ToType<std::string>(arguments[2]);

			for (auto m : modules)
			{
				if (m.Name == moduleName)
				{
					auto exports = m.GetExports();

					for (auto e : exports)
					{
						if (e.Name == functionName)
						{

							JObject jExport("export");
							jExport.AttachProperty(JProperty("name", Globals::ValueParser->ToJsValue<std::string>(e.Name)));
							jExport.AttachProperty(JProperty("address", Globals::ValueParser->ToJsValue<int>(e.Adress)));

							return jExport.Value;
						}
					}
				}
			}

			JObject jExport("export");
			jExport.AttachProperty(JProperty("name", Globals::ValueParser->ToJsValue<std::string>("Not found")));
			jExport.AttachProperty(JProperty("address", Globals::ValueParser->ToJsValue<int>(0x0000)));

			return jExport.Value;
		}

		JsValueRef CALLBACK JAddExceptionHandler(JsValueRef callee, bool isConstructCall, JsValueRef* arguments, unsigned short argCount, void* callbackState)
		{
			auto callback = arguments[1]; //the callback as [0] is "this"

			JException::AddHandler(callback);

			return 0;
			
		}

		JsValueRef CALLBACK JRemoveExceptionHandler(JsValueRef callee, bool isConstructCall, JsValueRef* arguments, unsigned short argCount, void* callbackState)
		{
			auto callback = arguments[1]; //the callback as [0] is "this"

			JException::RemoveHandler();

			return 0;
		}

		
	}

	namespace JAsm
	{
		JsValueRef CALLBACK JWriteShellcode(JsValueRef callee, bool isConstructCall, JsValueRef* arguments, unsigned short argCount, void* callbackState)
		{
			auto adress = Globals::ValueParser->ToType<int>(arguments[1]);
			auto shellcode = Assembler(KS_ARCH_X86, KS_MODE_32).Assemble(Globals::ValueParser->ToType<std::string>(arguments[2]));
			memcpy((void*)(adress), shellcode.data(), shellcode.size());
			return 0;
		}

		JsValueRef CALLBACK JPlaceShellCodeHook(JsValueRef callee, bool isConstructCall, JsValueRef* arguments, unsigned short argCount, void* callbackState)
		{
			auto adress = Globals::ValueParser->ToType<int>(arguments[1]);

			Hook().PlaceShellcodeHook(adress, Globals::ValueParser->ToType<std::string>(arguments[2]));
			return 0;
		}

		void _stdcall JsCallbackHookHandler(int argCount, int* format, int* params, JsValueRef callback)
		{
			std::string parameterFormat((char*)format);

			Globals::JavascriptRuntime->SetCurrentContext(); //always set the context before doing anything js related

			JsValueRef undefined;
			auto result = JsGetUndefinedValue(&undefined);
			
			std::vector<JsValueRef> functionParameters;

			functionParameters.push_back(undefined);

			for (auto p : ArgumentResolver(parameterFormat).ResolveArgsToJsVector(params))
				functionParameters.push_back(p);

			
			auto error = JsCallFunction(callback, functionParameters.data(), functionParameters.size(), NULL);

			if (error != 0)
			{
				MessageBoxA(0, "JsCallFunction failed.", "Hooking engine", 0);
			}
			
			Globals::JavascriptRuntime->DisposeContext(); //clean up the context
		}

		JsValueRef CALLBACK JPlaceCallbackHook(JsValueRef callee, bool isConstructCall, JsValueRef* arguments, unsigned short argCount, void* callbackState)
		{
			int count = 0;

			auto adress = Globals::ValueParser->ToType<int>(arguments[1]);
			auto format = Globals::ValueParser->ToType<std::string>(arguments[2]);

			count = ArgumentResolver::GetArgCount(format);

			auto callback = arguments[3];

			JCallback* c = new JCallback(count, format.c_str(), callback, (JCallback::JCallbackHandler)JsCallbackHookHandler); //making sure this nigga stays where he is.
			Hook().PlaceCallbackHook(adress, c);
			
			return 0;
		}

		JsValueRef CALLBACK JCallFunction(JsValueRef callee, bool isConstructCall, JsValueRef* arguments, unsigned short argCount, void* callbackState)
		{
			Globals::JavascriptRuntime->SetCurrentContext();

			int address = Globals::ValueParser->ToType<int>(JObject("nativeFunctionCall", arguments[0]).GetPropertyValueFromName("address"));
			auto call = JCall::GetFunctionCall(address);

			ArgumentResolver paramParser(call->Format);
			ArgumentResolver returnParser(call->ReturnFormat);

			int* parameters = new int[call->ArgCount];

			auto resources = paramParser.ResolveArgsToIntArray(arguments, parameters);

			call->Call(parameters);

			auto error = GetLastError();

			delete[] parameters;

			for (auto index : resources)
				Resource::RemoveResource(index);

			return returnParser.ResolveReturnValueToJsValue(call->ReturnValue);
		}

		JsValueRef CALLBACK JInitializeCall(JsValueRef callee, bool isConstructCall, JsValueRef* arguments, unsigned short argCount, void* callbackState)
		{
			auto adress = Globals::ValueParser->ToType<int>(arguments[1]);
			auto convention = static_cast<JCall::CallingConvention>(Globals::ValueParser->ToType<int>(arguments[2]));
			auto returnFormat = Globals::ValueParser->ToType<std::string>(arguments[3]);
			auto parameterFormat = Globals::ValueParser->ToType<std::string>(arguments[4]);

			int paramCount = ArgumentResolver::GetArgCount(parameterFormat);

			JCall* jCall = new JCall(adress, paramCount, convention, returnFormat.c_str(), parameterFormat.c_str());

			if(!JCall::ExistsFunctionCall(adress))
				JCall::AddFunctionCall(jCall);

			JCall::InitializeJCall(jCall);
			
			JObject jNativeFunctionCall("nativeFunctionCall");
			jNativeFunctionCall.AttachProperty(JProperty("address", Globals::ValueParser->ToJsValue<int>(adress)));
			jNativeFunctionCall.AttachFunction(JFunction("call", JAsm::JCallFunction));
			
			return jNativeFunctionCall.Value;
		}

		void __stdcall ManualCallbackHandler(JsValueRef callback)
		{
			Globals::JavascriptRuntime->SetCurrentContext();
			JsValueRef undefined;
			auto result = JsGetUndefinedValue(&undefined);

			JsValueRef* refs = new JsValueRef[1];

			refs[0] = undefined;

			auto r = JsCallFunction(callback, refs, 1, nullptr);

			delete[] refs;

			Globals::JavascriptRuntime->DisposeContext();
		}



		JsValueRef CALLBACK JPlaceManualHook(JsValueRef callee, bool isConstructCall, JsValueRef* arguments, unsigned short argCount, void* callbackState)
		{
			int address = Globals::ValueParser->ToType<int>(arguments[1]);
			std::string prologe = Globals::ValueParser->ToType<std::string>(arguments[2]);
			std::string epiloge = Globals::ValueParser->ToType<std::string>(arguments[3]);
			JsValueRef callback = arguments[4];


			JManualCallback* manualCallback = new JManualCallback(prologe.c_str(), epiloge.c_str(), callback, (JManualCallback::JManualCallbackHandler)ManualCallbackHandler);


			Hook().PlaceManualCallbackHook(address, manualCallback);

			return 0;
		}

	}

	void Initialize()
	{
		Globals::JavascriptRuntime->SetCurrentContext();
		auto global = Globals::JavascriptRuntime->GetGlobalObject();
		auto console = JObject("console");
		auto memory = JObject("memory");
		auto assembler = JObject("asm");
		auto protection = JObject("protection");
		auto winapi = JObject("winapi");
		auto callingConvention = JObject("callingConvention");

		console.AttachFunction(JFunction("alloc", JConsole::JAllocConsole));
		console.AttachFunction(JFunction("setTitle", JConsole::JSetConsoleTitle));
		console.AttachFunction(JFunction("free", JConsole::JFreeConsole));
		console.AttachFunction(JFunction("log", JConsole::JLog));

		memory.AttachFunction(JFunction("readInt", JMemory::JReadInt));
		memory.AttachFunction(JFunction("writeInt", JMemory::JWriteInt));
		memory.AttachFunction(JFunction("readBool", JMemory::JWriteBool));
		memory.AttachFunction(JFunction("writeBool", JMemory::JReadBool));
		memory.AttachFunction(JFunction("readString", JMemory::JReadString));
		memory.AttachFunction(JFunction("writeString", JMemory::JWriteString));
		memory.AttachFunction(JFunction("readFloat", JMemory::JReadFloat));
		memory.AttachFunction(JFunction("writeFloat", JMemory::JWriteFloat));
		memory.AttachFunction(JFunction("readDouble", JMemory::JReadDouble));
		memory.AttachFunction(JFunction("writeDouble", JMemory::JWriteDouble));

		memory.AttachFunction(JFunction("writeIntArray", JMemory::JWriteIntArray));
		memory.AttachFunction(JFunction("writeFloatArray", JMemory::JWriteFloatArray));
		memory.AttachFunction(JFunction("writeBoolArray", JMemory::JWriteBoolArray));
		memory.AttachFunction(JFunction("writeDoubleArray", JMemory::JWriteDoubleArray));

		memory.AttachFunction(JFunction("alloc", JMemory::JVirtualAlloc));
		memory.AttachFunction(JFunction("free", JMemory::JVirtualFree));
		memory.AttachFunction(JFunction("setProtection", JMemory::JVirtualProtect));
		memory.AttachFunction(JFunction("getProtection", JMemory::JVirtualQuery));

		protection.AttachProperty(JProperty("EXECUTE", Globals::ValueParser->ToJsValue<int>(PAGE_EXECUTE)));
		protection.AttachProperty(JProperty("EXECUTE_READ", Globals::ValueParser->ToJsValue<int>(PAGE_EXECUTE_READ)));
		protection.AttachProperty(JProperty("EXECUTE_READWRITE", Globals::ValueParser->ToJsValue<int>(PAGE_EXECUTE_READWRITE)));
		protection.AttachProperty(JProperty("EXECUTE_WRITECOPY", Globals::ValueParser->ToJsValue<int>(PAGE_EXECUTE_WRITECOPY)));

		protection.AttachProperty(JProperty("NOACCESS", Globals::ValueParser->ToJsValue<int>(PAGE_NOACCESS)));
		protection.AttachProperty(JProperty("READONLY", Globals::ValueParser->ToJsValue<int>(PAGE_READONLY)));
		protection.AttachProperty(JProperty("READWRITE", Globals::ValueParser->ToJsValue<int>(PAGE_READWRITE)));
		protection.AttachProperty(JProperty("WRITECOPY", Globals::ValueParser->ToJsValue<int>(PAGE_WRITECOPY)));


		assembler.AttachFunction(JFunction("writeShellcode", JAsm::JWriteShellcode));
		assembler.AttachFunction(JFunction("placeShellcodeHook", JAsm::JPlaceShellCodeHook));
		assembler.AttachFunction(JFunction("placeCallbackHook", JAsm::JPlaceCallbackHook));
		assembler.AttachFunction(JFunction("initializeCall", JAsm::JInitializeCall));
		assembler.AttachFunction(JFunction("placeManualHook", JAsm::JPlaceManualHook));

		winapi.AttachFunction(JFunction("getModules", JWinApi::JGetModules));
		winapi.AttachFunction(JFunction("getModule", JWinApi::JGetModule));
		winapi.AttachFunction(JFunction("getExports", JWinApi::JGetExports));
		winapi.AttachFunction(JFunction("getExport", JWinApi::JGetExport));
		winapi.AttachFunction(JFunction("addExceptionHandler", JWinApi::JAddExceptionHandler));

		callingConvention.AttachProperty(JProperty("stdcall", Globals::ValueParser->ToJsValue<int>(0)));
		callingConvention.AttachProperty(JProperty("cdecl", Globals::ValueParser->ToJsValue<int>(1)));
		callingConvention.AttachProperty(JProperty("thiscall", Globals::ValueParser->ToJsValue<int>(2)));


		global.AttachObject(console);
		global.AttachObject(memory);
		global.AttachObject(protection);
		global.AttachObject(assembler);
		global.AttachObject(winapi);
		global.AttachObject(callingConvention);
	}
}