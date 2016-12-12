#include "line.h"


#include <iostream>


std::ostream & operator<<(std::ostream & os, const std::pair<unsigned int, unsigned int> & result)
{
	if(result.second == 0)
	{
		std::cout << "\033[1;33m";
	}
	else if(result.first == result.second)
	{
		std::cout << "\033[1;32m";
	}
	else
	{
		std::cout << "\033[1;31m";
	}

	std::cout << result.first << " of " << result.second << " successful\033[0m" << std::endl;
}

int main(int argc, char *argv[])
{
	std::cout << "Line Unit Test ... " << Line::unitTest() << std::endl;




    return 0;
}
