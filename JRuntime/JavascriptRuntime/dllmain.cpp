// dllmain.cpp : Definiert den Einstiegspunkt für die DLL-Anwendung.
#include "stdafx.h"

/*
TODO:
-> Add __thiscall hooking and calling
-> Figure out what to do with structs that passed, what happens if we hook something which has not a native type -> read the address and read it from there therefore implement array reading and writing. 
-> Implement array reading and writing
-> Implement a short type, as windows requires it -> questionable
-> Implement exception handling as they will be thrown 100%
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

