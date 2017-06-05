#include "window.h"

namespace CLI
{

Window::Window(Data * data, const SizeHint & sizeHint)
: LayoutObject(true, sizeHint, WINDOW),
  visibleCollumns(1),
  visibleLines(1),
  lineOffset(1),
  collumnOffset(1),
  firstLineIndex(0),
  borderInverted(false),
  data(data)
{}


Window::~Window()
{}


void Window::setData(Data * data)
{
	this->data = data;
}


const LayoutObject::SizeHint& Window::getSizeHint()
{
	return defaultSizeHint;
}


LayoutObject::SizeHint Window::calcSizeHint()
{
	return defaultSizeHint;
}


void Window::setSize(unsigned int collumnOffset,
                     unsigned int lineOffset,
                     unsigned int width,
                     unsigned int height)
{
	this->collumnOffset = collumnOffset;
	this->lineOffset = lineOffset;
	this->width  = (width >= MIN_SIZE) ? width : MIN_SIZE;
	this->height = (height >= MIN_SIZE) ? height : MIN_SIZE;
	visibleLines   = this->width - 2;
	visibleCollumns = this->height - 2;
}


void Window::renderContent(ITerminal * terminal)
{
	unsigned int i = 0;
	for(std::list<Line*>::const_iterator it = data->getFirstLinesIter(firstLineIndex); it != data->getEndLineIter(); it++)
	{
		if(i++ >= visibleLines)
		{
			break;
		}

		terminal->printString((*it));
	}
}


void Window::renderBorder(ITerminal * terminal)
{
	terminal->printBorder(lineOffset, collumnOffset, height, width, borderInverted);
}


}
