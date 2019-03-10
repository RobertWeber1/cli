#include <cli/vt102.h>
#include <cli/serialize.h>
#include "catch.h"
#include "util.h"

using namespace cli;

TEST_CASE("generate vt102 commands")
{
	TestStream<10> stream;

	stream << VT102::QueryDeviceCode{} << flush;

	REQUIRE(stream.get_result() == "Hex{1b 5b 63}");
}
