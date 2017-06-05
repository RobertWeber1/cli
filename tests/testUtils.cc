#include "testUtils.h"


namespace CLI
{


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


std::string to_string( util::SizeConstraint const& constraint )
{
    std::stringstream result;
    result << "C(min: " << constraint.min_val() << ", max: " << constraint.max_val() << ", f: " << constraint.factor() << ")";
    return result.str();
}


std::string to_string( util::SizeHint const& size_hint )
{
    std::stringstream result;
    result << "Hwidth: " << to_string(size_hint.width()) << ", Hheight:" << to_string(size_hint.height());
    return result.str();
}


std::string to_string( border::Buffer & buffer )
{
    char char_map[16] = {
        ' ',//NONE         = 0b00000,
        '0',//UNUSED_1     = 0b00001,
        '0',//UNUSED_2     = 0b00010,
        '7',//BOTTOM_LEFT  = 0b00011,
        '0',//UNUSED_4     = 0b00100,
        '|',//VERTICAL     = 0b00101,
        '1',//TOP_LEFT     = 0b00110,
        '8',//TEE_RIGHT    = 0b00111,
        '0',//UNUSED_8     = 0b01000,
        '5',//BOTTOM_RIGHT = 0b01001,
        '-',//HORIZONTAL   = 0b01010,
        '6',//TEE_TOP      = 0b01011,
        '3',//TOP_RIGHT    = 0b01100,
        '4',//TEE_LEFT     = 0b01101,
        '2',//TEE_BOTTOM   = 0b01110,
        '+' //CROSS        = 0b01111,
    };
    std::stringstream borders;
    util::Point pos;
    border::Element *element;

    while( element = buffer.get( pos ) )
    {
        while( element = buffer.get( pos ) )
        {
            borders << element->to_char(char_map);
            pos.right();
        }
        borders << "\n";
        pos.break_line();
    }

    return borders.str();
}


}
