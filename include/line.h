#pragma once
#include <string>
#include <utility> //pair

namespace CLI
{


class Line
{
public:

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

    typedef enum Color{
        BLACK = 0,
        WHITE,
        RED,
        GREEN,
        BLUE,
        YELLOW,
        CYAN,
        MAGENTA
    }Color;

    typedef enum Alignment{
        LEFT = 0,
        CENTER,
        RIGHT
    }Alignment;

    static const std::string colorNames[];
    static const std::string attributeNames[];
    static const std::string alignmentNames[];


public:
    std::string text;
    Alignment alignment;
    Attribute attribute;
    Color forground;
    Color background;

    Line(const std::string & text = "",
         Color forground = WHITE,
         Color background = BLACK,
         Attribute attribute = NONE,
         Alignment alignment = LEFT);

    void dbgPrint(std::ostream & os) const;

    static std::pair<unsigned int, unsigned int> unitTest(bool verbose=true);
};


std::ostream & operator<<(std::ostream & os, const Line & line);
std::ostream & operator<<(std::ostream & os, const Line * line);
std::ostream & operator<<(std::ostream & os, Line::Color color);
std::ostream & operator<<(std::ostream & os, Line::Alignment alignment);
std::ostream & operator<<(std::ostream & os, Line::Attribute attribute);

}
