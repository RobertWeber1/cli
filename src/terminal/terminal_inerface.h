#pragma once

#include "util/point.h"
#include "util/properties.h"
#include "border.h"
#include <iostream>
#include <string>

namespace CLI
{

namespace terminal
{

class ITerminal
{
public:
	virtual ~ITerminal(){}

	virtual void clear_screen() = 0;

	virtual void set_cursor( util::Point const& ) = 0;
	virtual util::Point get_cursor() = 0;

	virtual void set_properties( util::Properties const& ) = 0;
	virtual util::Properties get_properties() = 0;

	virtual void set_normal_font();
	virtual void set_graphical_font();

	virtual void print_line( std::string const& ) = 0;
	virtual void print_line( std::string const&, util::Point const& ) = 0;

};

} //namespace terminal

} //namespace CLI
