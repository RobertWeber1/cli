#include "data.h"
#include <iostream>
#include <cstdio>

const std::map<std::String, int>  Data::commandMap = Data::initCommandMap();
const std::string Data::commandNames[] = {

};	

std::map<std::String> initCommandMap()
{
	std::map<std::String result;

	result[Data::ENABLE_AUTO_UPDATE] = 0;
	result[Data::DISABLE_AUTO_UPDATE] = 1;


	return result;
}

Data::Data()
{}


Data::~Data()
{}


void Data::processData()
{
	int inChar;
	while((inChar = this->get()) != EOF)
	{
		std::cout << "(" << inChar << ")" << " " << (char)inChar;
	}
}


void dbgToStream(std::ostream & os)
{

}



std::stringstream & operator(std::stringstream & str, Data::CommandID cmdID)
{
	str << 

	return str; 
}