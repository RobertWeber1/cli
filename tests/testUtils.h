#pragma once
#include "util/point.h"
#include "util/size.h"
#include "util/properties.h"
#include "util/size_constraint.h"
#include "util/size_hint.h"
#include "border/buffer.h"
#include "border/element.h"
#include <string>
#include <sstream>
#include <iostream>

namespace CLI
{

template<typename T>
void check( const std::string & func,
            const T & a,
            const T & b,
            std::pair<unsigned int, unsigned int> & result)
{
	result.second++;
    if(a == b)
    {
        result.first++;
    }
    else
    {
        std::cout << "\033[1;33m" << func << "\033[0m failed \nresult:\n" << a << "\nexpected:\n" << b << std::endl;
    }
}

std::ostream & operator<<( std::ostream & os, border::Element::Type type );

std::ostream & operator<<( std::ostream & os, util::Properties::Color color );
std::ostream & operator<<( std::ostream & os, util::Properties::Attribute attr );

std::string to_string( util::Point const& point );
std::string to_string( util::Size const& size );
std::string to_string( util::Properties const& prop );
std::string to_string( util::SizeConstraint const& constraint );
std::string to_string( util::SizeHint const& size_hint );
std::string to_string( border::Buffer & buffer );


}
