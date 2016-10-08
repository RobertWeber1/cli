#include "border.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <unistd.h>




void inline setCursorPostion(unsigned int column = 0, unsigned int line = 0, std::ostream& os=std::cout)
{
	os << "\033[" << line << ";" << column << "H" << std::flush;
}

void clearScreen(std::ostream & os = std::cout)
{
	os << "\033[2J";
	setCursorPostion(1,1,os);
}

void hideCursor(std::ostream& os=std::cout)
{
	std::cout << "\033[?25l" << std::flush;
}

void showCursor(std::ostream& os=std::cout)
{
	std::cout << "\033[?25h" << std::flush;
}

std::string NORMAL = "\033[m";
std::string INVERS = "\033[7m";

void printBorder(unsigned int column = 1, unsigned int line = 1, 
	             unsigned int width = 3, unsigned int height = 3,
	             const std::string & inverted = NORMAL,
	             char left = 'x', char right = 'x', 
	             char top = 'q',char bottom = 'q', 
	             char cornerTL = 'l', char cornerTR = 'k',
	             char cornerBL = 'm', char cornerBR = 'j',
	             std::ostream& os=std::cout)
{

	setCursorPostion(column, line, os);
	os << inverted << "\033(0" << cornerTL << std::setw(width-2) << std::setfill(top) << top << cornerTR;
	for(unsigned int i=1; i<height-1; i++)
	{
		setCursorPostion(column, line+i, os);
		os << left << "\033[" << (width-2) << "C" << right;
	}
	setCursorPostion(column, line+height-1, os);
	os << cornerBL << std::setw(width-2) << std::setfill(top) << top << cornerBR << "\033(B" << NORMAL << std::flush;

}

void fillRect(unsigned int column = 1, unsigned int line = 1, 
              unsigned int width = 1, unsigned int height = 1,
              char fillChar = '#', std::ostream& os=std::cout)
{
	setCursorPostion(column, line, os);
	for(unsigned int i=0; i<height; i++)
	{
		setCursorPostion(column, line+i, os);
		os << std::setw(width) << std::setfill(fillChar) << fillChar;
	} 
	os << std::flush;
}

int main(int argc, char *argv[])
{
	std::cout << "#---------- start terminal test ----------#" << std::endl;

	clearScreen();
	hideCursor();

	// printBorder(10, 10, 20, 10);
	// printBorder(29, 10, 20, 10);
	// printBorder(10, 19, 20, 10);

	// fillRect(11, 11, 18, 8, 'a');
	// //sleep(1);
	// fillRect(11, 11, 18, 8, 'b');

	// sleep(1);
	// printBorder(10, 10, 20, 10, INVERS);

	// sleep(1);
	// printBorder(10, 10, 20, 10);
	// //sleep(1);
	// setCursorPostion(1, 35);


	// for(char i = 33; i < 126; i++)
	// {
	// 	std::cout << i << " ";
	// }

	// std::cout<<"\033(0"<<std::endl;
	// for(char i = 33; i < 126; i++)
	// {
	// 	std::cout << i << " ";
	// }
	// std::cout << "\033(B" << std::endl;

	fillRect(1,1,60,30);
	setCursorPostion();
	BorderBuffer buffer(50, 25);

	buffer.setBorder(0,0, 10,10);

	buffer.setBorder(9,0, 10,10);

	buffer.setBorder(0,9, 10,10);

	buffer.setBorder(9,9, 10,10, true);

	buffer.setBorder(16,16, 50,50);

	buffer.toStream(std::cout);
	sleep(1);
	buffer.unsetInvertBorder(9,9, 10,10);
	buffer.setInvertBorder(9,0, 10,10);
	buffer.setInvertBorder(0,9, 10,10);
	buffer.unsetBorder(16,16, 50,50);
	setCursorPostion();
	buffer.toStream(std::cout);
	setCursorPostion(1, 30);
	std::cout << "\n\n#----------- end terminal test -----------#" << std::endl;
	showCursor();
}