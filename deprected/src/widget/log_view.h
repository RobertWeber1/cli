#pragma once
#include "util/line.h"
#include <streambuf>
#include <stdio.h>
#include <vector>

namespace CLI
{

namespace widget
{

class LineBuffer : public std::streambuf
{
public:
	virtual ~LineBuffer();

	void append_line( util::Line const & line );

	std::vector< util::Line > const& lines() const;

protected:
	int overflow ( int c = EOF );

	// std::streamsize xsputn (const char* s, std::streamsize n);

	int sync();

private:
	unsigned int max_lines;
	std::vector< util::Line > _lines;
};

} //namespace widget

} //namespace CLI
