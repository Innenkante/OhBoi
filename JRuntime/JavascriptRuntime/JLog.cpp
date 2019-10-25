#include "stdafx.h"
#include "JLog.h"

std::fstream JLog::logFile;

void JLog::Create(std::string name)
{
	logFile.open(name.c_str(), std::ios::in | std::ios::out | std::ios::app);
}

void JLog::Log(std::string message)
{
	auto time = std::time(nullptr);
	char timeAsString[64];
	ctime_s(timeAsString, sizeof(timeAsString), &time);

	auto trimmedTime = std::string(timeAsString).substr(0, strlen(timeAsString) - 1);

	logFile << "[" << trimmedTime.c_str() << "]:" << message << std::endl;

	logFile.flush();
}
