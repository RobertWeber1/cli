#include "line.h"
#include "testUtils.h"
#include <sstream>

namespace CLI
{

std::pair<unsigned int, unsigned int> Line::unitTest(bool verbose)
{
    unsigned int successful = 0;
    unsigned int count = 0;

    checkEq(attributeNames[NONE], "NONE", successful, count);
    checkEq(attributeNames[BOLD], "BOLD", successful, count);
    checkEq(attributeNames[DIM], "DIM", successful, count);
    checkEq(attributeNames[UNDERSCORE], "UNDERSCORE", successful, count);
    checkEq(attributeNames[BLINK], "BLINK", successful, count);
    checkEq(attributeNames[INVERSE], "INVERSE", successful, count);
    checkEq(attributeNames[HIDDEN], "HIDDEN", successful, count);

    checkEq(colorNames[BLACK], "BLACK", successful, count);
    checkEq(colorNames[WHITE], "WHITE", successful, count);
    checkEq(colorNames[RED], "RED", successful, count);
    checkEq(colorNames[GREEN], "GREEN", successful, count);
    checkEq(colorNames[BLUE], "BLUE", successful, count);
    checkEq(colorNames[YELLOW], "YELLOW", successful, count);
    checkEq(colorNames[CYAN], "CYAN", successful, count);
    checkEq(colorNames[MAGENTA], "MAGENTA", successful, count);

    checkEq(alignmentNames[LEFT], "LEFT", successful, count);
    checkEq(alignmentNames[CENTER], "CENTER", successful, count);
    checkEq(alignmentNames[RIGHT], "RIGHT", successful, count);

    Line l0("");
    std::stringstream testLine0;
    l0.dbgPrint(testLine0);
    checkEq(testLine0.str(), "Text: , Fg: WHITE, Bg: BLACK, Attr: NONE, Alignm: LEFT", successful, count);

    Line l1("BLA", Line::GREEN);
    std::stringstream testLine1;
    l1.dbgPrint(testLine1);
    checkEq(testLine1.str(), "Text: BLA, Fg: GREEN, Bg: BLACK, Attr: NONE, Alignm: LEFT", successful, count);

    Line l2("BLA2", Line::GREEN, Line::RED);
    std::stringstream testLine2;
    l2.dbgPrint(testLine2);
    checkEq(testLine2.str(), "Text: BLA2, Fg: GREEN, Bg: RED, Attr: NONE, Alignm: LEFT", successful, count);

    Line l3("BLA3", Line::BLUE, Line::MAGENTA, Line::BOLD);
    std::stringstream testLine3;
    l3.dbgPrint(testLine3);
    checkEq(testLine3.str(), "Text: BLA3, Fg: BLUE, Bg: MAGENTA, Attr: BOLD, Alignm: LEFT", successful, count);

    l3.text = "BLA4";
    l3.forground = Line::YELLOW;
    l3.background = Line::CYAN;
    l3.attribute = Line::DIM;
    l3.alignment = Line::CENTER;
    std::stringstream testLine4;
    l3.dbgPrint(testLine4);
    checkEq(testLine4.str(), "Text: BLA4, Fg: YELLOW, Bg: CYAN, Attr: DIM, Alignm: CENTER", successful, count);

    return std::pair<unsigned int, unsigned int>(successful, count);
}


}