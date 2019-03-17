#include <cli/vt102.h>
#include <cli/serialise.h>
#include "catch.h"
#include "util.h"

using namespace cli;

TEST_CASE("generate vt102 commands")
{
	TestStream<10> stream;

	SECTION("simple command")
	{
		stream << VT102<>::QueryDeviceCode{} << flush;
		REQUIRE(stream.get_result() == "Hex{1b 5b 63}");
	}

	SECTION("parameterized command")
	{
		stream
			<< VT102<>::SetCursorPosition(VT102<>::Row_t(40), VT102<>::Col_t(5))
			<< flush;

		REQUIRE(stream.get_result() == "Hex{1b 5b 34 30 3b 35 48}");
	}

	SECTION("set attributes")
	{
		stream
			<< VT102<>::SetAttribure<VT102<>::Attribute, VT102<>::Foreground, VT102<>::Background>(
				VT102<>::Attribute::Bright,
				VT102<>::Foreground::Black,
				VT102<>::Background::White)
			<< flush;

		REQUIRE(stream.get_result() == "Hex{1b 5b 31 3b 33 30 3b 34 37 6d}");
	}
}
