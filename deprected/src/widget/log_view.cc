#include "log_view.h"
#include <iostream>

namespace CLI
{

namespace widget
{


LineBuffer::~LineBuffer()
{}


void LineBuffer::append_line( util::Line const& /*line*/ )
{}


std::vector< util::Line > const& LineBuffer::lines() const
{
	return _lines;
}


int LineBuffer::overflow ( int c )
{
	std::cout << "LineBuffer::overflow char = " << c << std::endl;
}


// std::streamsize LineBuffer::xsputn (const char* s, std::streamsize n)
// {
// 	std::cout << "LineBuffer::xsputn: " << std::string( s, n) << std::endl;
// 	return n;
// }


int LineBuffer::sync()
{
	std::cout << "LineBuffer::overflow sync" << std::endl;
}





} //namespace widget

} //namespace CLI
