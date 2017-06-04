#include "unitTests.h"
#include "line.h"
#include "data.h"
#include "window.h"
#include <iostream>

int _has_failed_tests = 0;

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
		_has_failed_tests++;
		std::cout << "\033[1;31m";
	}
	std::cout << result.first << " of " << result.second << " successful\033[0m" << std::endl;
}


int main(int argc, char *argv[])
{
	std::cout << "Line Unit Test ... " << CLI::Line::unitTest() << std::endl;
	std::cout << "Data Unit Test ... " << CLI::Data::unitTest() << std::endl;
	std::cout << "Window Unit Test ... " << CLI::Window::unitTest() << std::endl;
	std::cout << "Border Unit Test ... " << border_unit_test() << std::endl;
    return _has_failed_tests;
}
