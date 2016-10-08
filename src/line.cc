#include "line.h"
#include <sstream>

const std::string Line::NORMAL = "\033[0m";
const std::string Line::Colors[]
{
    "37;40",
    "30;47",
    "31;40",
    "30;41",
    "32;40",
    "30;42",
    "34;40",
    "30;44",
    "33;40",
    "30;43",
    "36;40",
    "30;46",
    "35;40",
    "30;45"
};


Line::Line(const std::string & text, Color color, Attribute attribute, Alignment alignment):
    color(color), text(text), attribute(attribute), alignment(alignment)
{}


void Line::modifier(std::ostream& os) const
{
    os << "\033[" << Colors[color];
    if(attribute)
    {
        os << ";" << attribute;
    }
    os << "m";
}


void Line::toStream(std::ostream& os) const
{
    modifier(os);
    os << text << NORMAL;
}


std::ostream & operator<<(std::ostream & os, const Line & line)
{
    line.toStream(os);
    return os;
}


std::ostream & operator<<(std::ostream & os, const Line * line)
{
    line->toStream(os);
    return os;
}
