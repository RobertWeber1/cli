#include "line.h"
#include <iostream>


int main(int argc, char *argv[])
{
    int result = 0;

    std::cout << "LINETEST" << std::endl;

    // Line line0("white", Line::LEFT, Line::BOLD);
    // Line line1("inv_white", Line::LEFT, Line::NONE, Line::INV_WHITE);
    // Line line2("red", Line::LEFT, Line::NONE, Line::RED);
    // Line line3("inv_red", Line::LEFT, Line::NONE, Line::INV_RED);
    //
    //
    //
    // std::cout << "line0: " << line0 << std::endl;
    // std::cout << "line1: " << line1 << std::endl;
    // std::cout << "line2: " << line2 << std::endl;
    // std::cout << "line3: " << line3 << std::endl;


    Line lines[] =
    {
        Line("white", Line::WHITE),
        Line("inv_white", Line::INV_WHITE),
        Line("red", Line::RED),
        Line("inv_red", Line::INV_RED),
        Line("green", Line::GREEN),
        Line("inv_green", Line::INV_GREEN),
        Line("blue", Line::BLUE),
        Line("inv_blue", Line::INV_BLUE),
        Line("yellow", Line::YELLOW),
        Line("inv_yellow", Line::INV_YELLOW),
        Line("cyan", Line::CYAN),
        Line("inv_cyan", Line::INV_CYAN),
        Line("magenta", Line::MAGENTA),
        Line("inv_magenta", Line::INV_MAGENTA),

        Line("white fett", Line::WHITE, Line::BOLD),
        Line("inv_white fett", Line::INV_WHITE, Line::BOLD),
        Line("red fett", Line::RED, Line::BOLD),
        Line("inv_red fett", Line::INV_RED, Line::BOLD),
        Line("green fett", Line::GREEN, Line::BOLD),
        Line("inv_green fett", Line::INV_GREEN, Line::BOLD),
        Line("blue fett", Line::BLUE, Line::BOLD),
        Line("inv_blue fett", Line::INV_BLUE, Line::BOLD),
        Line("yellow fett", Line::YELLOW, Line::BOLD),
        Line("inv_yellow fett", Line::INV_YELLOW, Line::BOLD),
        Line("cyan fett", Line::CYAN, Line::BOLD),
        Line("inv_cyan fett", Line::INV_CYAN, Line::BOLD),
        Line("magenta fett", Line::MAGENTA, Line::BOLD),
        Line("inv_magenta fett", Line::INV_MAGENTA, Line::BOLD),

        Line("underscore", Line::WHITE, Line::UNDERSCORE),
        Line("blink", Line::WHITE, Line::BLINK),
        Line("inverse", Line::WHITE, Line::INVERSE),
        Line("hidden", Line::WHITE, Line::HIDDEN)
    };

    for(int i=0; i<32; i++)
    {
        std::cout << "line" << i << ": " << lines[i] << std::endl;
    }


    return result;
}
