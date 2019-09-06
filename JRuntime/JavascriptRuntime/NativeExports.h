#pragma once
#include "ChakraCore.h"
#include "Globals.h"
#include <string>
#define JExport extern "C" __declspec(dllexport)

JExport void LoadJavascriptFile(char* file);
JExport void UnloadJavascriptFile(char* file);