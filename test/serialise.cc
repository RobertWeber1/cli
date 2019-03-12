#include <cli/serialise.h>
#include "util.h"
#include "catch.h"

using namespace cli;


TEST_CASE("serialise CharSequence")
{
	TestStream<10> stream;
	stream << CharSequence<'a','b','c','0'>{} << flush;

	REQUIRE(stream.get_result() == "Hex{61 62 63 30}");
}


TEST_CASE("serialise unsigned int")
{
	TestStream<9> stream;

	SECTION("zero")
	{
		stream << int(0) << flush;
		REQUIRE(stream.get_result() == "Hex{30}");
	}

	SECTION("one digit")
	{
		stream << 1 << flush;
		REQUIRE(stream.get_result() == "Hex{31}");
	}

	SECTION("two digits")
	{
		stream << 12 << flush;
		REQUIRE(stream.get_result() == "Hex{31 32}");
	}

	SECTION("three digits")
	{
		stream << 123 << flush;
		REQUIRE(stream.get_result() == "Hex{31 32 33}");
	}

	SECTION("four digits")
	{
		stream << 1234 << flush;
		REQUIRE(stream.get_result() == "Hex{31 32 33 34}");
	}
}


TEST_CASE("serialise const char[]")
{
	TestStream<9> stream;

	SECTION("empty")
	{
		stream << "" << flush;
		REQUIRE(stream.get_result() == "Hex{22 22}");
	}

	SECTION("single char")
	{
		stream << "a" << flush;
		REQUIRE(stream.get_result() == "Hex{22 61 22}");
	}

	SECTION("multiple chars")
	{
		stream << "test 123" << flush;
		REQUIRE(stream.get_result() == "Hex{22 74 65 73 74 20 31 32 33 22}");
	}
}


TEST_CASE("serialise std::string")
{
	TestStream<9> stream;

	SECTION("empty")
	{
		stream << std::string("") << flush;
		REQUIRE(stream.get_result() == "Hex{22 22}");
	}

	SECTION("single char")
	{
		stream << std::string("a") << flush;
		REQUIRE(stream.get_result() == "Hex{22 61 22}");
	}

	SECTION("multiple chars")
	{
		stream << std::string("test 123") << flush;
		REQUIRE(stream.get_result() == "Hex{22 74 65 73 74 20 31 32 33 22}");
	}
}


TEST_CASE("serialise parameter sequence")
{
	TestStream<11> stream;

	SECTION("zero parameter")
	{
		stream << ParameterSequence<'c', CharSequence<'\033', '['>>{} << flush;

		REQUIRE(stream.get_result() == "Hex{1b 5b 63}");
	}

	SECTION("one parameter")
	{
		stream << ParameterSequence<'c', CharSequence<'\033', '['>, std::string>{"test"} << flush;

		REQUIRE(stream.get_result() == "Hex{1b 5b 22 74 65 73 74 22 63}");
	}

	SECTION("two parameter")
	{
		stream << ParameterSequence<'c', CharSequence<'\033', '['>, int, int>{5, 12} << flush;

		REQUIRE(stream.get_result() == "Hex{1b 5b 35 3b 31 32 63}");
	}

	SECTION("three parameter")
	{
		stream << ParameterSequence<'c', CharSequence<'\033', '['>, int, int, int>{5, 12, 345} << flush;

		REQUIRE(stream.get_result() == "Hex{1b 5b 35 3b 31 32 3b 33 34 35 63}");
	}
}