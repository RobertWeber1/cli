#include "data.h"
#include "testUtils.h"


namespace CLI
{

std::pair<unsigned int, unsigned int> Data::unitTest(bool verbose)
{
	unsigned int successful = 0;
    unsigned int count = 0;
	Data dat1;


	dat1 << "test line 1" << std::endl;
	dat1 << "test line 2" << std::endl;
	dat1 << "test line 3" << std::endl;
	dat1.processData();
	std::stringstream result;
	dat1.dbgPrint(result);
	checkEq(result.str(),
"Text: test line 1, Fg: WHITE, Bg: BLACK, Attr: NONE, Alignm: LEFT\n\
Text: test line 2, Fg: WHITE, Bg: BLACK, Attr: NONE, Alignm: LEFT\n\
Text: test line 3, Fg: WHITE, Bg: BLACK, Attr: NONE, Alignm: LEFT\n", successful, count);


	dat1 << Data::CLEAR_LINES;
	dat1.processData();
	std::stringstream result2;
	dat1.dbgPrint(result2);
	checkEq(result2.str(), "", successful, count);


	dat1 << Data::COLOR(Line::RED, Line::GREEN) << "test line 1" << std::endl;
	dat1 << Data::ALIGNMENT(Line::RIGHT) << "test line 2" << std::endl;
	dat1 << Data::ATTRIBUTE(Line::BOLD) << "test line 3" << std::endl;
	dat1.processData();
	std::stringstream result3;
	dat1.dbgPrint(result3);
	checkEq(result3.str(),
"Text: test line 1, Fg: RED, Bg: GREEN, Attr: NONE, Alignm: LEFT\n\
Text: test line 2, Fg: WHITE, Bg: BLACK, Attr: NONE, Alignm: RIGHT\n\
Text: test line 3, Fg: WHITE, Bg: BLACK, Attr: BOLD, Alignm: LEFT\n", successful, count);


	dat1 << Data::CLEAR_LINES;
	dat1 << "test line 1" << std::endl;
	dat1 << "test line 2" << std::endl;
	dat1 << "test line 3" << std::endl;
	dat1 << Data::INSERT_POS(Data::FRONT) << "test line 0" << std::endl;
	dat1.processData();
	std::stringstream result4;
	dat1.dbgPrint(result4);
	checkEq(result4.str(),
"Text: test line 0, Fg: WHITE, Bg: BLACK, Attr: NONE, Alignm: LEFT\n\
Text: test line 1, Fg: WHITE, Bg: BLACK, Attr: NONE, Alignm: LEFT\n\
Text: test line 2, Fg: WHITE, Bg: BLACK, Attr: NONE, Alignm: LEFT\n\
Text: test line 3, Fg: WHITE, Bg: BLACK, Attr: NONE, Alignm: LEFT\n", successful, count);


	dat1 << Data::INSERT_POS(Data::BACK);
	dat1 << Data::CLEAR_LINES;
	dat1 << "test line 1" << std::endl;
	dat1 << "test line 2" << std::endl;
	dat1 << "test line 3" << std::endl;
	dat1 << Data::INSERT_POS(Data::LINE_NUMBER, 2) << "test line insert" << std::endl;
	dat1.processData();
	std::stringstream result5;
	dat1.dbgPrint(result5);
	checkEq(result5.str(),
"Text: test line 1, Fg: WHITE, Bg: BLACK, Attr: NONE, Alignm: LEFT\n\
Text: test line 2, Fg: WHITE, Bg: BLACK, Attr: NONE, Alignm: LEFT\n\
Text: test line insert, Fg: WHITE, Bg: BLACK, Attr: NONE, Alignm: LEFT\n\
Text: test line 3, Fg: WHITE, Bg: BLACK, Attr: NONE, Alignm: LEFT\n", successful, count);

	dat1 << Data::EDIT_LINE(1) << "edited Line!!!!" << Data::COLOR(Line::BLUE, Line::YELLOW) << Data::EDIT_LINE(0) << "second edit" << std::endl;
	dat1.processData();
	std::stringstream result6;
	dat1.dbgPrint(result6);
	checkEq(result6.str(),
"Text: second edit, Fg: WHITE, Bg: BLACK, Attr: NONE, Alignm: LEFT\n\
Text: edited Line!!!!, Fg: BLUE, Bg: YELLOW, Attr: NONE, Alignm: LEFT\n\
Text: test line insert, Fg: WHITE, Bg: BLACK, Attr: NONE, Alignm: LEFT\n\
Text: test line 3, Fg: WHITE, Bg: BLACK, Attr: NONE, Alignm: LEFT\n", successful, count);


	return std::pair<unsigned int, unsigned int>(successful, count);
}


}
