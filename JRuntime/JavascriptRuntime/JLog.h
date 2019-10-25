#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <ctime>

class JLog
{
public:
	static void Create(std::string name);
	static void Log(std::string message);
private:
	static std::fstream logFile;
};

