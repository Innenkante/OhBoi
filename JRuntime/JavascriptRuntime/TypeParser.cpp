#include "stdafx.h"
#include "TypeParser.h"

TypeParser::TypeParser()
{
	parser[std::type_index(typeid(int))] = new IntParser();
	parser[std::type_index(typeid(double))] = new DoubleParser();
	parser[std::type_index(typeid(std::string))] = new StringParser();
	parser[std::type_index(typeid(bool))] = new BoolParser();
	parser[std::type_index(typeid(float))] = new FloatParser();
}
