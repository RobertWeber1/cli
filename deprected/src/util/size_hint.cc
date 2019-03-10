#include "size_hint.h"

namespace CLI
{

namespace util
{

SizeHint::SizeHint( SizeConstraint width, SizeConstraint height )
: _width(width)
, _height(height)
{}

void SizeHint::clear()
{
	_width.clear();
	_height.clear();
}


SizeConstraint const& SizeHint::width() const
{
	return _width;
}


SizeConstraint & SizeHint::width()
{
	return _width;
}


void SizeHint::width( SizeConstraint const& new_width )
{
	_width = new_width;
}


SizeConstraint const& SizeHint::height() const
{
	return _height;
}

SizeConstraint & SizeHint::height()
{
	return _height;
}

void SizeHint::height( SizeConstraint const& new_height )
{
	_height = new_height;
}


} //namespace util

} //namespace CLI
