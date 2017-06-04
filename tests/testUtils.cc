#include "testUtils.h"


namespace CLI
{

void checkEq(const std::string & a, const std::string & b, unsigned int & successful, unsigned int & count)
{
    count++;
    if(a == b)
    {
        successful++;
    }
    else
    {
        std::cout << "TEST[" << count << "] failed: string \"" << a << "\" should be equal to \"" << b << "\"" << std::endl;
    }
}

std::ostream & operator<<( std::ostream & os, border::Element::Type type )
{
    switch(type)
    {
    case border::Element::NONE:
        return os << "NONE";

    case border::Element::UNUSED_1:
        return os << "UNUSED_1";

    case border::Element::UNUSED_2:
        return os << "UNUSED_2";

    case border::Element::TOP_RIGHT:
        return os << "TOP_RIGHT";

    case border::Element::UNUSED_4:
        return os << "UNUSED_4";

    case border::Element::VERTICAL:
        return os << "VERTICAL";

    case border::Element::BOTTOM_RIGHT:
        return os << "BOTTOM_RIGHT";

    case border::Element::TEE_RIGHT:
        return os << "TEE_RIGHT";

    case border::Element::UNUSED_8:
        return os << "UNUSED_8";

    case border::Element::TOP_LEFT:
        return os << "TOP_LEFT";

    case border::Element::HORIZONTAL:
        return os << "HORIZONTAL";

    case border::Element::TEE_TOP:
        return os << "TEE_TOP";

    case border::Element::BOTTOM_LEFT:
        return os << "BOTTOM_LEFT";

    case border::Element::TEE_LEFT:
        return os << "TEE_LEFT";

    case border::Element::TEE_BOTTOM:
        return os << "TEE_BOTTOM";

    case border::Element::CROSS:
        return os << "CROSS";

    case border::Element::INVERT:
        return os << "INVERT";

    default:
        return os;
    }
}

std::ostream & operator<<( std::ostream & os, util::Properties::Color color )
{
    switch(color)
    {
    case util::Properties::BLACK:
        return os << "BLACK";

    case util::Properties::WHITE:
        return os << "WHITE";

    case util::Properties::RED:
        return os << "RED";

    case util::Properties::GREEN:
        return os << "GREEN";

    case util::Properties::BLUE:
        return os << "BLUE";

    case util::Properties::YELLOW:
        return os << "YELLOW";

    case util::Properties::CYAN:
        return os << "CYAN";

    case util::Properties::MAGENTA:
        return os << "MAGENTA";

    default:
        return os;
    }
}


std::ostream & operator<<( std::ostream & os, util::Properties::Attribute attr )
{
    switch(attr)
    {
    case util::Properties::NONE:
        return os << "NONE";

    case util::Properties::BOLD:
        return os << "BOLD";

    case util::Properties::DIM:
        return os << "DIM";

    case util::Properties::UNDERSCORE:
        return os << "UNDERSCORE";

    case util::Properties::BLINK:
        return os << "BLINK";

    case util::Properties::INVERSE:
        return os << "INVERSE";

    case util::Properties::HIDDEN:
        return os << "HIDDEN";

    default:
        return os;
    }
}


std::string to_string( util::Point const& point )
{
    std::stringstream result;
    result << "P(x: " << point.x() << ", y: " << point.y() << ")";
    return result.str();
}


std::string to_string( util::Size const& size )
{
    std::stringstream result;
    result << "S(w: " << size.width() << ", h: " << size.height() << ")";
    return result.str();
}


std::string to_string( util::Properties const& prop )
{
    std::stringstream result;
    result << "Prop(fg: " << prop.foreground() << ", bg: " << prop.background() << ", attr: " << prop.attribute() << ")";
    return result.str();
}


//----------------------------------------------------------------------------//


void TestTerminal::clearScreen()
{}


void TestTerminal::setForegroundColor(Line::Color)
{}


void TestTerminal::setBackgroundColor(Line::Color)
{}


void TestTerminal::setAttribute(Line::Attribute)
{}


void TestTerminal::resetAttributes()
{}


void TestTerminal::setCurserPosition(unsigned int line, unsigned int collumn)
{}


void TestTerminal::printString(const Line * line,
                 size_t start,
                 size_t len)
{
	output << line->text << std::endl;
}


void TestTerminal::printBorder(unsigned int lineNumber,
                 unsigned int collumnNumber,
                 unsigned int height,
                 unsigned int width,
                 bool inverted)
{}


}
