#include "border.h"
#include <string.h>

#include <iomanip>

const uint8_t BorderChar::INVERT_BORDER = 0x10;

const char BorderChar::simpleCharSet[16] = {
	' ',	//0: NONE
	' ',	//1: NONE
	' ',	//2: NONE
	'+',	//3: BOTTOM_LEFT
	' ',	//4: NONE
	'|',	//5: VERTICAL
	'+',	//6: TOP_LEFT
	'+',	//7: TEE_LEFT
	' ',	//8: NONE
	'+',	//9: BOTTOM_RIGHT
	'-',	//a: HORIZONTAL
	'+',	//b: TEE_TOP
	'+',	//c: TOP_RIGHT
	'+',	//d: TEE_RIGHT
	'+',	//e: TEE_BOTTOM
	'+'		//f: CROSS
};


//n o p q r s t u v w x y z { | } 
//┼ ⎺ ⎻ ─ ⎼ ⎽ ├ ┤ ┴ ┬ │ ≤ ≥ π ≠ £

const char BorderChar::graphicalCharSet[16] = {
	' ',	//0: NONE
	' ',	//1: NONE
	' ',	//2: NONE
	'm',	//3: BOTTOM_LEFT
	' ',	//4: NONE
	'x',	//5: VERTICAL
	'l',	//6: TOP_LEFT
	't',	//7: TEE_LEFT
	' ',	//8: NONE
	'j',	//9: BOTTOM_RIGHT
	'q',	//a: HORIZONTAL
	'v',	//b: TEE_TOP
	'k',	//c: TOP_RIGHT
	'u',	//d: TEE_RIGHT
	'w',	//e: TEE_BOTTOM
	'n'		//f: CROSS
};


uint8_t toBit(const BorderChar::BorderType & type, uint8_t bit)
{
	return (static_cast<uint8_t>(type) >> bit) & 0x01;
}


BorderChar::BorderChar(BorderType type) : 
	top(toBit(type,0)), 
	right(toBit(type,1)), 
	bottom(toBit(type,2)), 
	left(toBit(type,3)), 
	inverted(toBit(type,4))
{}


BorderChar& BorderChar::operator+(const BorderChar& borderChar)
{
	top += borderChar.top;
	right += borderChar.right;
	bottom += borderChar.bottom;
	left += borderChar.left;
	inverted += borderChar.inverted;
	return *this;
}


BorderChar& BorderChar::operator-(const BorderChar& borderChar)
{
	top -= borderChar.top;
	right -= borderChar.right;
	bottom -= borderChar.bottom;
	left -= borderChar.left;
	inverted -= borderChar.inverted;
	return *this;
}


BorderChar& BorderChar::operator=(const BorderChar& borderChar)
{
	top = borderChar.top;
	right = borderChar.right;
	bottom = borderChar.bottom;
	left = borderChar.left;
	inverted = borderChar.inverted;
	return *this;
}


BorderChar& BorderChar::operator+(const BorderType& borderType)
{
	top += toBit(borderType, 0);
	right += toBit(borderType, 1);
	bottom += toBit(borderType, 2);
	left += toBit(borderType, 3);
	inverted += toBit(borderType, 4);
	return *this;
}


BorderChar& BorderChar::operator-(const BorderType& borderType)
{
	top -= toBit(borderType, 0);
	right -= toBit(borderType, 1);
	bottom -= toBit(borderType, 2);
	left -= toBit(borderType, 3);
	inverted -= toBit(borderType, 4);
	return *this;
}


BorderChar& BorderChar::operator=(const BorderType& borderType)
{
	top = toBit(borderType, 0);
	right = toBit(borderType, 1);
	bottom = toBit(borderType, 2);
	left = toBit(borderType, 3);
	inverted = toBit(borderType, 4);
	return *this;
}


void BorderChar::setInvert(bool value)
{
	if(value)
	{
	    inverted++;
	}
	else
	{
	    inverted--;
	}
}


uint8_t BorderChar::toIndex()
{
	return ((top)?1:0) | ((right)?2:0)| ((bottom)?4:0) | ((left)?8:0);
}


void BorderChar::toStream(std::ostream & os, bool graphical)
{
	if(graphical)
	{
		os << graphicalCharSet[toIndex()];
	}
	else
	{
		os << simpleCharSet[toIndex()];
	}
	
}


bool BorderChar::isNone()
{
	bool result = true;

	if(top != 0)
	{
		result = false;
	}
	else if(right != 0)
	{
		result = false;
	}
	else if(bottom != 0)
	{
		result = false;
	}
	else if(left != 0)
	{
		result = false;
	}

	return result;
}


BorderChar::BorderType BorderChar::getType()
{
	int result = 0;

	if(top != 0)
	{
		result |= 1;
	}
	if(right != 0)
	{
		result |= 2;
	}
	if(bottom != 0)
	{
		result |= 4;
	}
	if(left != 0)
	{
		result |= 8;
	}

	return static_cast<BorderType>(result);
}


//----------------------------------------------------------------------------//

BorderBuffer::BorderBuffer(unsigned int width, unsigned int height) : 
	width(width) ,height(height), buffer(NULL)
{
	setSize(width, height);
}

BorderBuffer::~BorderBuffer()
{
	if(buffer)
	{
		delete[] buffer;
	}
}

void BorderBuffer::setSize(unsigned int width, unsigned int height)
{
	if(width == 0)
	{
		width = 1;
	}
	if(height == 0)
	{
		height = 1;
	}

	if(buffer != NULL)
	{
		if((width*height) > (this->width*this->height))
		{
			delete[] buffer;
			buffer = new BorderChar[width*height];
		}
	}
	else
	{
		buffer = new BorderChar[width*height];
	}

	this->width = width;
	this->height = height;

	clear();
}

void BorderBuffer::setBorder(unsigned int column, 
                             unsigned int line,
                             unsigned int boxWidth,
                             unsigned int boxHeight,
                             bool inverted)
{
	unsigned int currentColumn = column;
	unsigned int currentLine   = line;

	BorderChar::BorderType inv = (inverted)?BorderChar::INVERT : BorderChar::NONE;

	if(column < width && line < height)
	{
		while(currentLine < height)
		{
			if(currentLine == line || currentLine == (line + boxHeight-1))
			{
				if(currentColumn != column && currentColumn != column+boxWidth-1)
				{
					buffer[currentLine*width+currentColumn] + BorderChar::HORIZONTAL + inv;
				}
				else if(currentColumn == column)
				{
					if(currentLine == line)
					{
						buffer[currentLine*width+currentColumn] + BorderChar::TOP_LEFT + inv;
					}
					else
					{
						buffer[currentLine*width+currentColumn] + BorderChar::BOTTOM_LEFT + inv;
					}
				}
				else
				{
					if(currentLine == line)
					{
						buffer[currentLine*width+currentColumn] + BorderChar::TOP_RIGHT + inv;
					}
					else
					{
						buffer[currentLine*width+currentColumn] + BorderChar::BOTTOM_RIGHT + inv;
					}
				}
				currentColumn++;
			}
			else
			{
				if(currentColumn == column || currentColumn == (column + boxWidth -1))
				{
					buffer[currentLine*width+currentColumn] + BorderChar::VERTICAL + inv;
				}
				currentColumn += boxWidth - 1;
			}

			if(currentColumn >= width || currentColumn >= column+boxWidth)
			{
				currentColumn = column;
				currentLine++;
				if(currentLine >= height || currentLine >= line+boxHeight)
				{
					break;
				}
			}
		}
	}
}


void BorderBuffer::setInvertBorder(unsigned int column, 
                                   unsigned int line, 
                                   unsigned int boxWidth,
                                   unsigned int boxHeight)
{
	unsigned int currentColumn = column;
	unsigned int currentLine   = line;

	if(column < width && line < height)
	{
		while(currentLine < height)
		{
			if(currentLine == line || currentLine == (line + boxHeight-1))
			{
				if(currentColumn != column && currentColumn != column+boxWidth-1)
				{
					buffer[currentLine*width+currentColumn] + BorderChar::INVERT;
				}
				else if(currentColumn == column)
				{
					if(currentLine == line)
					{
						buffer[currentLine*width+currentColumn] + BorderChar::INVERT;
					}
					else
					{
						buffer[currentLine*width+currentColumn] + BorderChar::INVERT;
					}
				}
				else
				{
					if(currentLine == line)
					{
						buffer[currentLine*width+currentColumn] + BorderChar::INVERT;
					}
					else
					{
						buffer[currentLine*width+currentColumn] + BorderChar::INVERT;
					}
				}
				currentColumn++;
			}
			else
			{
				if(currentColumn == column || currentColumn == (column + boxWidth -1))
				{
					buffer[currentLine*width+currentColumn] + BorderChar::INVERT;
				}
				currentColumn += boxWidth - 1;
			}

			if(currentColumn >= width || currentColumn >= column+boxWidth)
			{
				currentColumn = column;
				currentLine++;
				if(currentLine >= height || currentLine >= line+boxHeight)
				{
					break;
				}
			}
		}
	}
}


void BorderBuffer::unsetBorder(unsigned int column, 
                               unsigned int line, 
                               unsigned int boxWidth,
                               unsigned int boxHeight,
                               bool inverted)
{
	unsigned int currentColumn = column;
	unsigned int currentLine   = line;

	BorderChar::BorderType inv = (inverted)?BorderChar::INVERT : BorderChar::NONE;

	if(column < width && line < height)
	{
		while(currentLine < height)
		{
			if(currentLine == line || currentLine == (line + boxHeight-1))
			{
				if(currentColumn != column && currentColumn != column+boxWidth-1)
				{
					buffer[currentLine*width+currentColumn] - BorderChar::HORIZONTAL - inv;
				}
				else if(currentColumn == column)
				{
					if(currentLine == line)
					{
						buffer[currentLine*width+currentColumn] - BorderChar::TOP_LEFT - inv;
					}
					else
					{
						buffer[currentLine*width+currentColumn] - BorderChar::BOTTOM_LEFT - inv;
					}
				}
				else
				{
					if(currentLine == line)
					{
						buffer[currentLine*width+currentColumn] - BorderChar::TOP_RIGHT - inv;
					}
					else
					{
						buffer[currentLine*width+currentColumn] - BorderChar::BOTTOM_RIGHT - inv;
					}
				}
				currentColumn++;
			}
			else
			{
				if(currentColumn == column || currentColumn == (column + boxWidth -1))
				{
					buffer[currentLine*width+currentColumn] - BorderChar::VERTICAL - inv;
				}
				currentColumn += boxWidth - 1;
			}

			if(currentColumn >= width || currentColumn >= column+boxWidth)
			{
				currentColumn = column;
				currentLine++;
				if(currentLine >= height || currentLine >= line+boxHeight)
				{
					break;
				}
			}
		}
	}
}

void BorderBuffer::unsetInvertBorder(unsigned int column, 
                                     unsigned int line, 
                                     unsigned int boxWidth,
                                     unsigned int boxHeight)
{
	unsigned int currentColumn = column;
	unsigned int currentLine   = line;

	if(column < width && line < height)
	{
		while(currentLine < height)
		{
			if(currentLine == line || currentLine == (line + boxHeight-1))
			{
				if(currentColumn != column && currentColumn != column+boxWidth-1)
				{
					buffer[currentLine*width+currentColumn] - BorderChar::INVERT;
				}
				else if(currentColumn == column)
				{
					if(currentLine == line)
					{
						buffer[currentLine*width+currentColumn] - BorderChar::INVERT;
					}
					else
					{
						buffer[currentLine*width+currentColumn] - BorderChar::INVERT;
					}
				}
				else
				{
					if(currentLine == line)
					{
						buffer[currentLine*width+currentColumn] - BorderChar::INVERT;
					}
					else
					{
						buffer[currentLine*width+currentColumn] - BorderChar::INVERT;
					}
				}
				currentColumn++;
			}
			else
			{
				if(currentColumn == column || currentColumn == (column + boxWidth -1))
				{
					buffer[currentLine*width+currentColumn] - BorderChar::INVERT;
				}
				currentColumn += boxWidth - 1;
			}

			if(currentColumn >= width || currentColumn >= column+boxWidth)
			{
				currentColumn = column;
				currentLine++;
				if(currentLine >= height || currentLine >= line+boxHeight)
				{
					break;
				}
			}
		}
	}
}

void BorderBuffer::clear()
{
	for(unsigned int i = 0; i<height; i++)
	{
		for(unsigned int j=0; j<width; j++)
		{
			buffer[i*width+j] = BorderChar::NONE;
		}
	}
}


void BorderBuffer::toStream(std::ostream & os)
{
	uint8_t inverted = 0;
	unsigned int noneCount = 0;
	std::stringstream space;

	os << "\033(0";
	for(unsigned int i=0; i<height; i++)
	{
		for(unsigned int j=0; j<width; j++)
		{
			if(not buffer[i*width+j].isNone())
			{
				if(noneCount != 0)
				{
					os << "\033[" << noneCount << "C";
					noneCount = 0;
				}

				if(buffer[i*width+j].inverted != inverted)
				{
					if(buffer[i*width+j].inverted == 0)
					{
						os << "\033[m";
					}
					else
					{
						os << "\033[7m";
					}
					inverted = buffer[i*width+j].inverted;
				}

				buffer[i*width+j].toStream(os);
			}
			else
			{
				noneCount++;
			}
		}

		os << "\n";
		noneCount = 0;
	}
	os << "\033(B" << std::flush;
}

//----------------------------------------------------------------------------//


Border::Border(char topLeft, char top, char topRight,
               char left, char right,
               char bottomLeft, char bottom, char bottomRight,
               char middleEnd1, char middle, char middleEnd2) :
	topLeft(topLeft), top(top), topRight(topRight),
	left(left), right(right),
	bottomLeft(bottomLeft), bottom(bottom), bottomRight(bottomRight),
	middleEnd1(middleEnd1), middle(middle), middleEnd2(middleEnd2)
{}
