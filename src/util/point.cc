#include "point.h"

namespace CLI
{

namespace util
{

Point::Point( unsigned int x, unsigned int y )
: _x(x)
, _y(y)
{}

Point::Point( Point const& point )
: _x( point.x() )
, _y( point.y() )
{}

unsigned int Point::x() const
{
	return _x;
}

unsigned int Point::y() const
{
	return _y;
}

void Point::x( unsigned int new_x )
{
	_x = new_x;
}

void Point::y( unsigned int new_y )
{
	_y = new_y;
}

void Point::left( unsigned int x_offset )
{
	_x -= x_offset ;
}

void Point::right( unsigned int x_offset )
{
	_x += x_offset ;
}

void Point::up( unsigned int y_offset )
{
	_y -= y_offset ;
}

void Point::down( unsigned int y_offset )
{
	_y += y_offset ;
}

void Point::break_line()
{
	_x = 0;
	_y++;
}

void Point::set( unsigned int new_x, unsigned int new_y )
{
	_x = new_x;
	_y = new_y;
}


} //namespace util

} //namespace CLI
