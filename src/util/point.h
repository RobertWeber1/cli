#pragma once

namespace CLI
{

namespace util
{

class Point
{
public:
	Point( unsigned int x = 0, unsigned int y = 0 )
	: _x(x)
	, _y(y)
	{}

	Point( Point const& point )
	: _x( point.x() )
	, _y( point.y() )
	{}

	unsigned int x() const
	{
		return _x;
	}

	unsigned int y() const
	{
		return _y;
	}

	void x( unsigned int new_x )
	{
		_x = new_x;
	}

	void y( unsigned int new_y )
	{
		_y = new_y;
	}

	void left( unsigned int x_offset = 1 )
	{
		_x -= x_offset ;
	}

	void right( unsigned int x_offset = 1 )
	{
		_x += x_offset ;
	}

	void up( unsigned int y_offset = 1 )
	{
		_y -= y_offset ;
	}

	void down( unsigned int y_offset = 1 )
	{
		_y += y_offset ;
	}

	void break_line()
	{
		_x = 0;
		_y++;
	}

	void set( unsigned int new_x = 0, unsigned int new_y = 0 )
	{
		_x = new_x;
		_y = new_y;
	}

private:
	unsigned int _x;
	unsigned int _y;
};


} //namespace util

} //namespace CLI
