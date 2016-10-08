#include "cliwindow.h"
#include <cmath>
#include <algorithm>
#include <iostream>
#include <iomanip>

CLIWindow::CLIWindow(const SizeHint & sizeHint, unsigned int maxLineCount):
	LayoutObject(true, sizeHint),
	maxLineCount(maxLineCount),
	topIndex(0),
	stickyBottom(true)
{}


CLIWindow::~CLIWindow()
{
	clearLookupInfo();
	clearLines();
}


void CLIWindow::trimFront()
{
	while(lines.size() > maxLineCount)
	{
		removeLookup(screenLookupInfos.front()->line, screenLookupInfos);
		delete lines.front();
		lines.pop_front();
	}
}


void CLIWindow::trimBack()
{
	while(lines.size() > maxLineCount)
	{
		removeLookup(screenLookupInfos.back()->line, screenLookupInfos);
		delete lines.back();
		lines.pop_back();
	}
}


void CLIWindow::appendLine(const std::string & text,
                           Line::Color color,
                           Line::Attribute attribute,
                           Line::Alignment alignment)
{
	lines.push_back(new Line(text, color, attribute, alignment));
	unsigned int newLockupCount = generateLookup(lines.back(), screenLookupInfos, width, screenLookupInfos.end());
	trimFront();
	if(stickyBottom)
	{
		scrollDown(newLockupCount);
	}
}


void CLIWindow::insertLine(unsigned int index,
                           const std::string & text,
                           Line::Color color,
                           Line::Attribute attribute,
                           Line::Alignment alignment)
{
	Line *newLine = new Line(text, color, attribute, alignment);
	lines.insert(lines.begin()+index, newLine);

	unsigned int insertIndex = 0;

	if(index != 0)
	{
		bool foundLookupBefore=false;
		for(std::deque<ScreenLookupInfo*>::iterator it = screenLookupInfos.begin(); it != screenLookupInfos.end(); it++)
		{
			if((*it)->line == lines[index - 1])
			{
				foundLookupBefore = true;
			}
			if(foundLookupBefore && (*it)->line != lines[index - 1])
			{
				break;
			}
			insertIndex++;
		}
	}

	generateLookup(newLine, screenLookupInfos, width, screenLookupInfos.begin()+insertIndex);

	if(index == 0)
	{
		trimBack();
	}
	else
	{
		trimFront();
	}
}


void CLIWindow::replaceLine(unsigned int index,
                            const std::string & text,
                            Line::Color color,
                            Line::Attribute attribute,
                            Line::Alignment alignment)
{
	removeLine(index);
	insertLine(index, text, color, attribute, alignment);
}


bool CLIWindow::removeLine(unsigned int index)
{
	bool result = false;

	if(index < lines.size())
	{
		std::deque<Line*>::iterator it = lines.begin()+index;

		removeLookup(*it, screenLookupInfos);

		delete *it;
		lines.erase(it);

		result = true;
	}

	return result;
}


void CLIWindow::clearLines()
{
	for(std::deque<Line*>::iterator it = lines.begin(); it != lines.end(); it++)
	{
		delete *it;
	}
	lines.clear();
}


void CLIWindow::clearLookupInfo()
{
	topIndex = 0;
	for(std::deque<ScreenLookupInfo*>::iterator it = screenLookupInfos.begin(); it != screenLookupInfos.end(); it++)
	{
		delete *it;
	}
	screenLookupInfos.clear();
}


unsigned int CLIWindow::generateLookup(Line* line,
                                       std::deque<ScreenLookupInfo*>& dest,
                                       unsigned int width,
                                       std::deque<ScreenLookupInfo*>::iterator position)
{
	std::deque<ScreenLookupInfo*> result;

	unsigned int offset = 0;
	unsigned int lookupCount = ceil((float)line->text.size()/(float)width);

	std::cout << "DEBUG text: "<< line->text.size() 
	          << ", width: " << width 
	          << ", lookupCount: " << lookupCount << std::endl;

	if(lookupCount == 0)
	{
		result.push_back(new ScreenLookupInfo(line, 0, 0));
	}
	else
	{
		for(unsigned int i=0; i<lookupCount; i++)
		{
			unsigned int currWidth = std::min(width, (unsigned int)(line->text.size() - offset));
			result.push_back(new ScreenLookupInfo(line, offset, currWidth));
			offset += width;
		}
	}

	dest.insert(position, result.begin(), result.end());

	return result.size();
}


unsigned int CLIWindow::removeLookup(Line* lineToRemove, std::deque<ScreenLookupInfo*>& source)
{
	unsigned int offset = 0;
	bool foundLine      = false;
	unsigned int count  = 0;

	for(unsigned int i=0; i<screenLookupInfos.size(); i++)
	{
		if(foundLine && screenLookupInfos[i]->line != lineToRemove)
		{
			break;
		}

		if(screenLookupInfos[i]->line == lineToRemove)
		{
			if(!foundLine)
			{
				offset = i;
				foundLine = true;
			}
			count++;
			delete screenLookupInfos[i];
		}
	}

	if(foundLine)
	{
		screenLookupInfos.erase(screenLookupInfos.begin()+offset, screenLookupInfos.begin()+offset+count);
	}

	return count;
}


void CLIWindow::scrollUp(unsigned int count)
{
	stickyBottom = false;

	if(topIndex >= count)
	{
		topIndex -= count;
	}
	else
	{
		topIndex = 0;
	}
}


void CLIWindow::scrollDown(unsigned int count)
{
	if(screenLookupInfos.size() >= (topIndex + height + count))
	{
		topIndex += count;
	}
	else
	{

		topIndex = screenLookupInfos.size() - height;
		stickyBottom = true;
	}
}


void CLIWindow::scrollToTop()
{
	topIndex = 0;
	stickyBottom = false;
}


void CLIWindow::scrollToBottom()
{
	if(screenLookupInfos.size() > height)
	{
		topIndex = screenLookupInfos.size() - height;
		stickyBottom = true;
	}
}


unsigned int CLIWindow::Height() const
{
	return height;
}


unsigned int CLIWindow::Width() const
{
	return width;
}


void CLIWindow::printLines()
{
	unsigned int count = 0;
	for(std::deque<Line*>::iterator it = lines.begin(); it != lines.end(); it++)
	{
		std::cout << "Line" << count << ": " << (*it)->text << std::endl;
		count++;
	}
}


void CLIWindow::printLookup()
{
	unsigned int count = 0;
	for(std::deque<ScreenLookupInfo*>::iterator it = screenLookupInfos.begin(); it != screenLookupInfos.end(); it++)
	{
		std::cout << "Lookup" << count << "  " 
		          << "offset: " << (*it)->offset 
		          << ", width: " << (*it)->width 
		          << ", textpart: " << (*it)->line->text.substr((*it)->offset, (*it)->width) << std::endl;
		count++;
	}
}


// const LayoutObject::Size& CLIWindow::getSizeConstraint()
// {
// 	return sizeHint;
// }

const LayoutObject::SizeHint& CLIWindow::getSizeHint()
{
	return defaultSizeHint;
}

LayoutObject::SizeHint CLIWindow::calcSizeHint()
{
	return defaultSizeHint;
}


void CLIWindow::printLine(std::ostream & os, unsigned int index, const Border & border) const
{
	unsigned int relIndex = index + topIndex;
	if(relIndex < screenLookupInfos.size())
	{
		if(border.left != 0)
		{
			os << border.left; 
		}


		const char* start = screenLookupInfos[relIndex]->line->text.c_str() + screenLookupInfos[relIndex]->offset;
		os.write(start, screenLookupInfos[relIndex]->width);

		unsigned int space = lineWidth - screenLookupInfos[relIndex]->width;
		if(space > 0)
		{
			os << "\033[" << space << "C";
		}

		if(border.right != 0)
		{
			os << border.right; 
		}
		
	}
	else
	{
		unsigned int curWidth = lineWidth;

		if(border.left != 0)
		{
			os << border.left;
		}

		os << std::setw(lineWidth) << std::setfill(' ') << " ";
		//os << "\033[" << curWidth << "C";

		if(border.right != 0)
		{
			os << border.right; 
		}
		
	}
}


void CLIWindow::toStream(std::ostream& os, unsigned int lineIndex) const
{
	if(lineIndex < height)
	{
		unsigned int relIndex = lineIndex + topIndex;
		if(relIndex < screenLookupInfos.size())
		{
			const char* start = screenLookupInfos[relIndex]->line->text.c_str() + screenLookupInfos[relIndex]->offset;
			os.write(start, screenLookupInfos[relIndex]->width);

			unsigned int space = width - screenLookupInfos[relIndex]->width;
			if(space > 0)
			{
				os << "\033[" << space << "C";
			}
		}

		// if(lineIndex == 0)
		// {
		// 	if(border.top != 0)
		// 	{
		// 		if(border.topLeft)
		// 		{
		// 			os << border.topLeft;
		// 		}
		// 		if(border.top)
		// 		{
		// 			os << std::setw(lineWidth) 
		// 			   << std::setfill(border.top) << border.top;
		// 		}
		// 		if(border.topRight)
		// 		{
		// 			os << border.topRight;
		// 		}
		// 	}
		// 	else
		// 	{
		// 		printLine(os, lineIndex, border);
		// 	}
		// }
		// else if(lineIndex == height-1)
		// {
		// 	if( border.bottom != 0)
		// 	{
		// 		if(border.bottomLeft)
		// 		{
		// 			os << border.bottomLeft;
		// 		}
		// 		if(border.bottom)
		// 		{
		// 			os << std::setw(lineWidth) 
		// 			   << std::setfill(border.bottom) << border.bottom;
		// 		}
		// 		if(border.bottomRight)
		// 		{
		// 			os << border.bottomRight;
		// 		}
		// 	}
		// 	else
		// 	{
		// 		printLine(os, lineIndex, border);
		// 	}
		// }
		// else
		// {
		// 	printLine(os, lineIndex, border);
		// }
	}
}


void CLIWindow::setSize(unsigned int width, unsigned int height, const Border & border)
{
	this->height = height;
	this->width  = width;
	this->border = border;
	
	lineHeight   = height - ((border.top!=0)?1:0)  - ((border.bottom!=0)?1:0);

	unsigned int newLineWidth = width - ((border.left!=0)?1:0)  - ((border.right!=0)?1:0);
	if(lineWidth != newLineWidth)
	{
		if(screenLookupInfos.size() != 0)
		{
			Line* topLinePointer = screenLookupInfos[topIndex]->line;

			clearLookupInfo();
			for(std::deque<Line*>::iterator it = lines.begin(); it != lines.end(); it++)
			{
				generateLookup(*it, screenLookupInfos, newLineWidth, screenLookupInfos.end());
			}

			topIndex = 0;
			while(screenLookupInfos[topIndex]->line != topLinePointer && (topIndex + height)<screenLookupInfos.size())
			{
				scrollDown(1);
			}
		}

		lineWidth = newLineWidth;
	}

	std::cout << "CLIWindow::setSize() width: " << this->width 
	          << "(" << lineWidth << "), height: " << this->height 
	          << "(" << lineHeight << ")" << std::endl;

}


void CLIWindow::borderToBuffer(BorderBuffer& buffer, unsigned int lineOffset, unsigned int columnOffset)
{
	
}