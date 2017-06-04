#include "window.h"
#include "testUtils.h"

namespace CLI
{

void window_printToTerminal
(unsigned int & count, unsigned int & successful)
{
	TestTerminal term;
	Data data;
	Window win(&data);
	data << "some line 1" << std::endl;
	data.processData();

	win.renderContent(&term);

	check<std::string>(__FUNCTION__, term.output.str(), "some line 1\n", successful, count);
}


std::pair<unsigned int, unsigned int> Window::unitTest(bool verbose)
{
	unsigned int successful = 0;
    unsigned int count = 0;

    window_printToTerminal(count, successful);

    return std::pair<unsigned int, unsigned int>(successful, count);
}

}
