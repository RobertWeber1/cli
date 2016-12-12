#include "data.h"
#include <iostream>

int main(int argc, char * argv[])
{
	Data dat1;

	dat1 << "test1" << std::endl;
	dat1 << "test2" << std::endl;
	dat1 << "test3" << std::endl;

	std::cout << "1. process:" << std::endl;
	dat1.processData();


	dat1 << "test4" << std::endl;
	std::cout << "2. process:" << std::endl;
	dat1.processData();

	// std::cout << "LOOP:" << std::endl;
	// for(int i=0; i<1000; i++)
	// {
	// 	dat1 << "looptests" << i << std::endl;
	// 	dat1.processData();
	// }

	std::cout << "Color test1:" << std::endl;
	dat1 << Data::SET_COLOR(Line::RED, Line::GREEN);
	dat1.processData();

	std::cout << "Color test2:" << std::endl;
	dat1 << Data::SET_COLOR(Line::BLUE, Line::MAGENTA) << Data::SET_COLOR(Line::RED, Line::GREEN);
	dat1.processData();

	std::cout << "Alignment test:" << std::endl;
	dat1 << Data::SET_ALIGNMENT(Line::LEFT) << Data::SET_ALIGNMENT(Line::CENTER) << Data::SET_ALIGNMENT(Line::RIGHT);
	dat1.processData();

	std::cout << "Line test:" << std::endl;
	dat1 << Data::SET_LINE(Data::FRONT);
	dat1 << Data::SET_LINE(Data::BACK);
	dat1 << Data::SET_LINE(Data::LINE_NUMBER, 0x1000);
	dat1.processData();



	return 0;
}