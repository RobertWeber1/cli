#pragma once
#include <sstream>
#include <iostream>
#include <stdint.h>
#include <streambuf>

 
class BorderChar
{
public:
	//     2^1
	//      |
 	//2^4 -- -- 2^2
 	//      |
 	//     2^3
	typedef enum BorderType
	{
		NONE         = 0x00, //0b0000,
		TOP_LEFT     = 0x06, //0b0110,
		HORIZONTAL   = 0x0a, //0b1010,
		TOP_RIGHT    = 0x0c, //0b1100,
		VERTICAL     = 0x05, //0b0101,
		BOTTOM_LEFT  = 0x03, //0b0011,
		BOTTOM_RIGHT = 0x09, //0b1001,
		TEE_LEFT     = 0x07, //0b0111,
		TEE_RIGHT    = 0x0d, //0b1101,
		TEE_BOTTOM   = 0x0e, //0b1110,
		TEE_TOP      = 0x0b, //0b1011,
		CROSS        = 0x0e, //0b1111
		INVERT       = 0x10
	}BorderType;

	static const uint8_t INVERT_BORDER;
	static const char simpleCharSet[16];
	static const char graphicalCharSet[16];

	
public:
	//BorderType type;
	uint8_t inverted;
	uint8_t top;
	uint8_t right;
	uint8_t bottom;
	uint8_t left;

	BorderChar(BorderType type = NONE);
	BorderChar& operator+(const BorderChar& borderChar);
	BorderChar& operator-(const BorderChar& borderChar);
	BorderChar& operator=(const BorderChar& borderChar);
	BorderChar& operator+(const BorderType& borderType);
	BorderChar& operator-(const BorderType& borderType);
	BorderChar& operator=(const BorderType& borderType);
	
	uint8_t toIndex();

	void setInvert(bool value = false);
	void toStream(std::ostream & os, bool graphical = true);
	bool isNone();
	BorderType getType();
};


class BorderBuffer
{
private:
	unsigned int width;
	unsigned int height;
	//uint8_t *buffer;
	BorderChar *buffer;

public:
	BorderBuffer(unsigned int width = 3, unsigned int height = 3);
	~BorderBuffer();

	void setSize(unsigned int width, unsigned int height);
	void setBorder(unsigned int column, 
	               unsigned int line, 
	               unsigned int width, 
	               unsigned int height, 
	               bool inverted = false);
	void setInvertBorder(unsigned int column, 
	                     unsigned int line, 
	                     unsigned int width, 
	                     unsigned int height);
	void unsetBorder(unsigned int column, 
	                 unsigned int line, 
	                 unsigned int width, 
	                 unsigned int height, 
	                 bool inverted = false);
	void unsetInvertBorder(unsigned int column, 
	                       unsigned int line, 
	                       unsigned int width, 
	                       unsigned int height);
	void clear();
	void toStream(std::ostream & os);
};


class Border
{
public:
	unsigned int width;
	unsigned int height;
	char topLeft, top, topRight;
	char left, right;
	char bottomLeft, bottom, bottomRight;
	char middleEnd1, middle, middleEnd2;

	Border(char topLeft=0, char top=0, char topRight=0,
		   char left=0, char right=0,
		   char bottomLeft=0, char bottom=0, char bottomRight=0,
		   char middleEnd1=0, char middle=0, char middleEnd2=0);
};
