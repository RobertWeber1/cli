#pragma once
#include "line.h"



namespace CLI
{

class ITerminal
{
protected:
	Line::Attribute currentAttribute;
	Line::Color     currentForground;
	Line::Color     currentBackground;

public:
	virtual void clearScreen() = 0;

	virtual void setForegroundColor(Line::Color) = 0;
	virtual void setBackgroundColor(Line::Color) = 0;
	virtual void setAttribute(Line::Attribute) = 0;
	virtual void resetAttributes() = 0;

	virtual void setCurserPosition(unsigned int line, unsigned int collumn) = 0;

	virtual void printString(const Line * line,
	                         size_t start = 0,
	                         size_t len = std::string::npos) = 0;
	virtual void printBorder(unsigned int lineNumber,
	                         unsigned int collumnNumber,
	                         unsigned int height,
	                         unsigned int width,
	                         bool inverted) = 0;
};

}
