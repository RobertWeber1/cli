#include "line.h"
#include "util.h"
#include <sstream>
#include <iostream>

namespace CLI
{

const std::string Line::attributeNames[] = {
    "NONE",
    "BOLD",
    "DIM",
    "UNDERSCORE",
    "BLINK",
    "INVERSE",
    "HIDDEN"
};

const std::string Line::colorNames[] = {
    "BLACK",
    "WHITE",
    "RED",
    "GREEN",
    "BLUE",
    "YELLOW",
    "CYAN",
    "MAGENTA"
};


const std::string Line::alignmentNames[] = {
    "LEFT",
    "CENTER",
    "RIGHT"
};


std::ostream & operator<<(std::ostream & os, const Line & line)
{
    line.dbgPrint(os);
    return os;
}


std::ostream & operator<<(std::ostream & os, const Line * line)
{
    line->dbgPrint(os);
    return os;
}


std::ostream & operator<<(std::ostream & os, Line::Color color)
{
    os << Line::colorNames[color];
    return os;
}


std::ostream & operator<<(std::ostream & os, Line::Alignment alignment)
{
    os << Line::alignmentNames[static_cast<int>(alignment)];
    return os;
}


std::ostream & operator<<(std::ostream & os, Line::Attribute attribute)
{
    os << Line::attributeNames[attribute];
    return os;
}


Line::Line(const std::string & text, Color forground, Color background, Attribute attribute, Alignment alignment):
    text(text), forground(forground), background(background), attribute(attribute), alignment(alignment)
{}


void Line::dbgPrint(std::ostream & os) const
{
    os << "Text: " << text << ", Fg: " << forground << ", Bg: " << background << ", Attr: " << attribute << ", Alignm: " << alignment;
}




}
