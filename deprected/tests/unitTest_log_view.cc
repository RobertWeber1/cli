#include "catch.h"
#include "widget/log_view.h"

TEST_CASE( "Foo" )
{
	CLI::widget::LineBuffer line_buffer;

	std::ostream out(&line_buffer);

	out << "test" << std::endl;
}