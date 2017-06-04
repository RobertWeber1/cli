#pragma once
#include "terminal.h"
#include "util/point.h"
#include "util/size.h"
#include "util/properties.h"
#include "border/element.h"
#include <string>
#include <sstream>
#include <iostream>

namespace CLI
{

void checkEq( const std::string & a, const std::string & b, unsigned int & successful, unsigned int & count);

template<typename T>
void check( const std::string & func,
            const T & a,
            const T & b,
            unsigned int & successful,
            unsigned int & count)
{
	count++;
    if(a == b)
    {
        successful++;
    }
    else
    {
        std::cout << "\033[1;33m" << func << "\033[0m failed \nresult:\n" << a << "\nexpected:\n" << b << std::endl;
    }
}


template<typename T>
void check( const std::string & func,
            const T & a,
            const T & b,
            std::pair<unsigned int, unsigned int> & result)
{
	check( func, a, b, result.first, result.second);
}


class TestTerminal : public ITerminal
{
public:
	std::stringstream output;

	virtual ~TestTerminal() {}

	void clearScreen();
	void setForegroundColor(Line::Color);
	void setBackgroundColor(Line::Color);
	void setAttribute(Line::Attribute);
	void resetAttributes();
	void setCurserPosition(unsigned int line, unsigned int collumn);
	void printString(const Line * line,
	                 size_t start = 0,
	                 size_t len = std::string::npos);
	void printBorder(unsigned int lineNumber,
	                 unsigned int collumnNumber,
	                 unsigned int height,
	                 unsigned int width,
	                 bool inverted);
};

std::ostream & operator<<( std::ostream & os, border::Element::Type type );

std::ostream & operator<<( std::ostream & os, util::Properties::Color color );
std::ostream & operator<<( std::ostream & os, util::Properties::Attribute attr );

std::string to_string( util::Point const& point );
std::string to_string( util::Size const& size );
std::string to_string( util::Properties const& prop );

}
