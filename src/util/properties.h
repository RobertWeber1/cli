#pragma once

namespace CLI
{

namespace util
{

typedef struct Properties
{

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

	Properties( Color fg = WHITE, Color bg = BLACK, Attribute attr = NONE )
	: foreground(fg)
	, background(bg)
	, attribute(attr)
	{}
	// Color foreground() const;

	// Color background() const;

	// Attribute attribute() const;

	// void foreground( Color fg );

	// void background( Color bg );

	// void attribute( Attribute attr );

	Color foreground;
	Color background;
	Attribute attribute;
}Properties;

} //namespace util

} //namespace CLI
