#pragma once

namespace CLI
{

namespace util
{

class Properties
{
public:
	typedef enum Color
	{
		BLACK,
		WHITE,
		RED,
		GREEN,
		BLUE,
		YELLOW,
		CYAN,
		MAGENTA
	}Color;

	typedef enum Attribute
	{
		NONE = 0,
		BOLD,
		DIM,
		UNDERSCORE,
		BLINK,
		INVERSE,
		HIDDEN
	}Attribute;

	Properties( Color fg = WHITE, Color bg = BLACK, Attribute attr = NONE );
	// : _foreground(fg)
	// , _background(bg)
	// , _attribute(attr)
	// {}

	Color foreground() const;
	// {
	// 	return _foreground;
	// }

	Color background() const;
	// {
	// 	return _background;
	// }

	Attribute attribute() const;
	// {
	// 	return _attribute;
	// }

	void foreground( Color fg );
	// {
	// 	_foreground = fg;
	// }

	void background( Color bg );
	// {
	// 	_background = bg;
	// }

	void attribute( Attribute attr );
	// {
	// 	_attribute = attr;
	// }

private:
	Color _foreground;
	Color _background;
	Attribute _attribute;
};

} //namespace util

} //namespace CLI
