#include <cli/serialize.h>
// #include <cli/vt102.h>
#include "util.h"
#include "catch.h"

using namespace cli;

TEST_CASE("serialize CharSequence")
{
	TestStream<10> stream;
	stream << CharSequence<'a','b','c','0'>{} << flush;
	// stream.flush();

	REQUIRE(stream.get_result() == "Hex{61 62 63 30}");
}