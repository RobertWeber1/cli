#pragma once

namespace CLI
{

namespace util
{

class Point
{
public:
	Point( unsigned int x = 0, unsigned int y = 0 );

	Point( Point const& point );

	unsigned int x() const;

	unsigned int y() const;

	void x( unsigned int new_x );

	void y( unsigned int new_y );

	void left( unsigned int x_offset = 1 );

	void right( unsigned int x_offset = 1 );

	void up( unsigned int y_offset = 1 );

	void down( unsigned int y_offset = 1 );

	void break_line();

	void set( unsigned int new_x = 0, unsigned int new_y = 0 );

private:
	unsigned int _x;
	unsigned int _y;
};


} //namespace util

} //namespace CLI
