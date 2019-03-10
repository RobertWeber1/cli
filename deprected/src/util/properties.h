#pragma once
#include "color.h"
#include "attribute.h"
#include "alignment.h"

namespace CLI
{

namespace util
{

typedef struct Properties
{
	Properties( Color fg = WHITE, Color bg = BLACK, Attribute attr = NONE, Alignment align = LEFT )
	: foreground( fg )
	, background( bg )
	, attribute( attr )
	, alignment( align )
	{}

	Color foreground;
	Color background;
	Attribute attribute;
	Alignment alignment;
}Properties;

} //namespace util

} //namespace CLI
