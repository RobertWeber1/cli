#include "size.h"

namespace CLI
{

namespace util
{

Size::Size( unsigned int width, unsigned int height )
: _width(width)
, _height(height)
{}

unsigned int Size::width() const
{
	return _width;
}

unsigned int Size::height() const
{
	return _height;
}

void Size::width( unsigned int new_width )
{
	_width = new_width;
}

void Size::height( unsigned int new_height )
{
	_height = new_height;
}

void Size::zero()
{
	_height = 0;
	_width = 0;
}

Size Size::trim( Size const& max_size ) const
{
	return Size( ( (_width<max_size.width()) ? _width : max_size.width() )
	           , ( (_height<max_size.height()) ? _height : max_size.height() ) );
}


} //namespace util

} //namespace CLI
