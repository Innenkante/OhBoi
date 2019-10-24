// dllmain.cpp : Definiert den Einstiegspunkt für die DLL-Anwendung.
#include "stdafx.h"
#include <fstream>

/*
TODO:
-> Add __thiscall hooking and calling
-> Refactor the exception handling as it works now.
-> Add a log to file capability
-> Implement a "pointer" type?! instead of using int
-> Implement a short type, as windows requires it -> questionable
-> Add a graphic library and export a ui namespace to make overlay drawing possible
*/

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

