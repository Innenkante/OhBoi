#pragma once
#include <Windows.h>
#include <winnt.h>
#include <winternl.h>

#include <vector>
class ExportedFunction
{
public:
	std::string Name;
	int Adress;

private:

};


class Module
{
public:
	Module(PLDR_DATA_TABLE_ENTRY entry);
	std::string Name;
	std::string Path;
	int DllBase;

	std::vector<ExportedFunction> GetExports();
private:

};

class PEBParser
{
public:
	std::vector<Module> GetModules();
	PTEB GetTEB();
private:
	
};
