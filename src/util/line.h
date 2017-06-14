#pragma once
#include "properties.h"
#include "alignment.h"

namespace CLI
{

namespace util
{

typedef struct Line
{
	Line(std::string const& text, Properties const& properties, Alignment alignment)
	: text(text)
	, properties(properties)
	, alignment(alignment)
	{}

	std::string text;
	Properties  properties;
	Alignment   alignment;
}Line;


} //namespace util

} //namespace CLI
