// dllmain.cpp : Definiert den Einstiegspunkt für die DLL-Anwendung.
#include "stdafx.h"

/*
TODO:
-> Add __thiscall hooking and calling
-> Implement a "pointer" type?! instead of using int
-> Implement a short type, as windows requires it -> questionable
-> Implement exception handling as they will be thrown 100% => kind of done, don't know what's wrong there. 
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

