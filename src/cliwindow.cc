#include "cliwindow.h"
#include <cmath>
#include <algorithm>
#include <iostream>
#include <iomanip>

CLIWindow::CLIWindow(const SizeHint & sizeHint, unsigned int maxLineCount):
	LayoutObject(true, sizeHint, WINDOW),
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

	std::cout << "scrollUp topIndex: " << topIndex << std::endl;
}


void CLIWindow::scrollDown(unsigned int count)
{
	std::cout << "before scrollDown topIndex: " << topIndex << std::endl;
	if(screenLookupInfos.size() >= (topIndex + lineHeight + count))
	{
		topIndex += count;
	}
	else
	{
		if(screenLookupInfos.size() > lineHeight)
		{
			topIndex = screenLookupInfos.size() - lineHeight;
		}
		stickyBottom = true;
	}
	std::cout << "after scrollDown topIndex: " << topIndex << std::endl;
}


void CLIWindow::scrollToTop()
{
	topIndex = 0;
	stickyBottom = false;
}


void CLIWindow::scrollToBottom()
{
	if(screenLookupInfos.size() > lineHeight)
	{
		topIndex = screenLookupInfos.size() - lineHeight;
		stickyBottom = true;
	}
	std::cout << "scrollToBottom topIndex: " << topIndex << std::endl;
}


unsigned int CLIWindow::Height() const
{
	return height;
}


unsigned int CLIWindow::Width() const
{
	return width;
}


unsigned int CLIWindow::LineHeight() const
{
	return lineHeight;
}

unsigned int CLIWindow::LineWidth() const
{
	return lineWidth;
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


const LayoutObject::SizeHint& CLIWindow::getSizeHint()
{
	return defaultSizeHint;
}

LayoutObject::SizeHint CLIWindow::calcSizeHint()
{
	return defaultSizeHint;
}


void CLIWindow::toStream(std::ostream& os) const
{
	unsigned int currentColumn = columnOffset + 1;
	unsigned int currentLine   = lineOffset + 1;

	for(int lineIndex=0; lineIndex<lineHeight; lineIndex++)
	{
		os << "\033[" << currentLine << ";" << currentColumn << "H";
		unsigned int relIndex = lineIndex + topIndex;
		if(relIndex < screenLookupInfos.size())
		{
			const char* start = screenLookupInfos[relIndex]->line->text.c_str() + screenLookupInfos[relIndex]->offset;
			os.write(start, screenLookupInfos[relIndex]->width);

			unsigned int space = width - screenLookupInfos[relIndex]->width;
			if(space > 0)
			{
				os << std::setw(space) << std::setfill(' ') << " ";
			}
		}
		else
		{
			os << std::setw(lineWidth) << std::setfill(' ') << " ";
		}
		currentLine++;
	}
}


void CLIWindow::setSize(unsigned int columnOffset,
	                    unsigned int lineOffset, 
	                    unsigned int width, 
	                    unsigned int height)
{
	this->columnOffset = columnOffset;
	this->lineOffset = lineOffset;
	this->width  = width;
	this->height = height;
	
	lineHeight   = height - 2;

	unsigned int newLineWidth = width - 2;
	if(lineWidth != newLineWidth)
	{
		if(screenLookupInfos.size() != 0)
		{
			std::cout << "test1 topIndex: " << topIndex << std::endl;
			Line* topLinePointer = screenLookupInfos[topIndex]->line;
			clearLookupInfo();
			for(std::deque<Line*>::iterator it = lines.begin(); it != lines.end(); it++)
			{
				generateLookup(*it, screenLookupInfos, newLineWidth, screenLookupInfos.end());
			}

			std::cout << "test2" << std::endl;
			topIndex = 0;
			if(not screenLookupInfos.empty())
			{
				while(screenLookupInfos[topIndex]->line != topLinePointer && (topIndex + height)<screenLookupInfos.size())
				{
					scrollDown(1);
				}
			}
			std::cout << "test3" << std::endl;
		}

		lineWidth = newLineWidth;
	}

	//std::cout << "CLIWindow::setSize() " 
	//          << "x: " << std::setw(3) << columnOffset << ", Y: " << std::setw(3) << lineOffset
	//          << ", width: " << std::setw(3) << this->width << "(" << std::setw(3) << lineWidth 
	//          << "), height: " << std::setw(3) << this->height << "(" << std::setw(3) << lineHeight << ")" << std::endl;

}


void CLIWindow::borderToBuffer(BorderBuffer& buffer)
{
	buffer.setBorder(columnOffset-1, lineOffset-1, width, height);
}