#pragma once
#include "line.h"
#include "layoutobject.h"
#include <vector>
#include <deque>


class CLIWindow : public LayoutObject
{
public:
	typedef struct ScreenLookupInfo
	{
		Line* line;
		unsigned int offset;
		unsigned int width;
		ScreenLookupInfo(Line* line, unsigned int offset, unsigned int width):
			line(line), offset(offset), width(width) {}
	}ScreenLookupInfo;

private:
	unsigned int maxLineCount;
	unsigned int topIndex;
	bool stickyBottom;
	Border border;
	std::deque<Line*> lines;
	std::deque<ScreenLookupInfo*> screenLookupInfos;
	unsigned int lineWidth, lineHeight;

	void clearLines();
	void clearLookupInfo();

	void trimFront();
	void trimBack();

	void printLine(std::ostream & os, 
		           unsigned int index, 
		           const Border & border = Border()) const;

public:
	CLIWindow(const SizeHint & sizeHint = SizeHint(), unsigned int maxLineCount=100);
	virtual ~CLIWindow();

	void appendLine(const std::string & text,
	                Line::Color color = Line::WHITE,
	                Line::Attribute=Line::NONE,
	                Line::Alignment=Line::LEFT);
	void insertLine(unsigned int index,
	                const std::string & text,
	                Line::Color color=Line::WHITE,
	                Line::Attribute attribute=Line::NONE,
	                Line::Alignment alignment=Line::LEFT);
	void replaceLine(unsigned int index,
	                const std::string & text,
	                Line::Color color=Line::WHITE,
	                Line::Attribute attribute=Line::NONE,
	                Line::Alignment alignment=Line::LEFT);
	bool removeLine(unsigned int index);

	unsigned int generateLookup(Line* line,
	                            std::deque<ScreenLookupInfo*>& dest,
	                            unsigned int width,
	                            std::deque<ScreenLookupInfo*>::iterator position);
	unsigned int removeLookup(Line* line, std::deque<ScreenLookupInfo*>& source);

	void scrollUp(unsigned int count);
	void scrollDown(unsigned int count);

	void scrollToTop();
	void scrollToBottom();

	unsigned int Height() const;
	unsigned int Width() const;

	void printLines();
	void printLookup();


	SizeHint calcSizeHint();
	const SizeHint& getSizeHint();
	void setSize(unsigned int width, 
	             unsigned int height, 
	             const Border & border = Border());
	void toStream(std::ostream& os, unsigned int lineIndex) const;
	void borderToBuffer(BorderBuffer& buffer, unsigned int lineOffset, unsigned int columnOffset);
};
