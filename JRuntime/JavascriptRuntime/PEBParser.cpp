#include "stdafx.h"
#include "PEBParser.h"
#include <string>
#include <iostream>

std::vector<Module> PEBParser::GetModules()
{
	std::vector<Module> modules;

	auto peb = GetTEB()->ProcessEnvironmentBlock;

	auto ldr = peb->Ldr;

	auto head = &ldr->InMemoryOrderModuleList;

	PLIST_ENTRY entry = head->Flink;

	while (entry != head)
	{
		auto record = CONTAINING_RECORD(entry, LDR_DATA_TABLE_ENTRY, InMemoryOrderLinks);

		modules.push_back(Module(record));

		entry = entry->Flink;
	}


	return modules;
}

PTEB PEBParser::GetTEB()
{
	auto teb = reinterpret_cast<PTEB>(__readfsdword(reinterpret_cast<DWORD_PTR>(&static_cast<NT_TIB*>(nullptr)->Self)));

	return teb;
}

Module::Module(PLDR_DATA_TABLE_ENTRY entry)
{
	auto fullDllNameW = std::wstring(entry->FullDllName.Buffer);
	auto baseDllNameW = std::wstring(((UNICODE_STRING*)entry->Reserved4)->Buffer);
	auto fullDllNameA = std::string(fullDllNameW.begin(), fullDllNameW.end());
	auto baseDllNameA = std::string(baseDllNameW.begin(), baseDllNameW.end());

	this->Path = fullDllNameA;
	this->Name = baseDllNameA;
	this->DllBase = (int)entry->DllBase;
}

std::vector<ExportedFunction> Module::GetExports()
{
	std::vector<ExportedFunction> exportedFunctions;
	auto dosHeader = (IMAGE_DOS_HEADER*)DllBase;

	auto ntHeader = (IMAGE_NT_HEADERS*)(DllBase + dosHeader->e_lfanew);

	auto exportDirectory = (IMAGE_EXPORT_DIRECTORY*)(DllBase + ntHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);

	//TODO check if exportDirectory even exists, example: .exe has no exports therefore it crashes.

	if (exportDirectory->NumberOfFunctions == 0)
		return exportedFunctions;

	auto nameAdress = DllBase + exportDirectory->AddressOfNames;
	auto functionAdress = (int*)(DllBase + exportDirectory->AddressOfFunctions);
	auto functionOrdinal = (short*)(DllBase + exportDirectory->AddressOfNameOrdinals);
	auto numberOfNames = exportDirectory->NumberOfNames;
	

	for (int i = 0; i < numberOfNames; i++)
	{
		ExportedFunction e;
		auto string = *(int*)(nameAdress + i * sizeof(int));
		e.Name = std::string((char*)(DllBase + string));

		auto address = functionAdress[functionOrdinal[i]];

		e.Adress = DllBase + address;

		exportedFunctions.push_back(e);
	}
	return exportedFunctions;
}
