#pragma once
#include <string>

class Line
{
public:
    typedef enum Alignment
    {
        LEFT,
        CENTER,
        RIGHT,
    }Alignment;

    typedef enum Attribute
    {
        NONE       = 0,
        BOLD       = 1,
        DIM        = 2,
        UNDERSCORE = 4,
        BLINK      = 5,
        INVERSE    = 7,
        HIDDEN     = 8
    }Attribute;

    typedef enum Color
    {
        WHITE = 0,
        INV_WHITE,
        RED,
        INV_RED,
        GREEN,
        INV_GREEN,
        BLUE,
        INV_BLUE,
        YELLOW,
        INV_YELLOW,
        CYAN,
        INV_CYAN,
        MAGENTA,
        INV_MAGENTA
    }Color;

private:
    static const std::string Colors[];
    static const std::string NORMAL;


public:
    std::string text;
    Alignment alignment;
    Attribute attribute;
    Color color;
    
    Line(const std::string & text,
         Color color = WHITE,
         Attribute attribute = NONE,
         Alignment alignment = LEFT);

    // void setText(const std::string & newText);
    // void setAlignment(Alignment newAlignment);
    // void setAttribute(Attribute newAttribute);
    // void setColor(Color newColor);
    void modifier(std::ostream & os) const;
    void toStream(std::ostream & os) const;
};


std::ostream & operator<<(std::ostream & os, const Line & line);
std::ostream & operator<<(std::ostream & os, const Line * line);
