#include <cli/output_stream.h>
#include "catch.h"
#include "util.h"

struct OutStreamTest : cli::OutputStream<OutStreamTest>, TestResult<>
{
	using  Out_t = cli::OutputStream<OutStreamTest>;

	OutStreamTest(uint8_t * data, size_t size)
	: Out_t(data, size)
	{}

	template<size_t N>
	OutStreamTest(uint8_t (&data)[N])
	: Out_t(data)
	{}


	size_t flush()
	{
		uint32_t ret = 0;

		if(flush_size != -1)
		{
			ret = flush_size;
		}
		else
		{
			ret = head - begin;
		}

		result_.push("flush(" + std::to_string(ret) + ")");
		return ret;
	}

	int flush_size = -1;
};


TEST_CASE("output stream")
{
	uint8_t buffer[10];
	OutStreamTest stream(buffer);

	SECTION("check initial properties of stream")
	{
		REQUIRE(stream.begin == buffer);
		REQUIRE(stream.end == buffer+10);

		REQUIRE(stream.has_capacity(9));
		REQUIRE(stream.has_capacity(10));
		REQUIRE_FALSE(stream.has_capacity(11));

		REQUIRE(stream == make_hex(""));
	}

	SECTION("no need for flush")
	{
		REQUIRE(stream.advance(1));

		REQUIRE(stream.has_capacity(9));
		REQUIRE(stream.get_result() == "");
	}

	SECTION("flush needed")
	{
		REQUIRE(stream.advance(5));

		REQUIRE(stream.has_capacity(9));
		REQUIRE(stream.get_result() == "flush(5)");
	}
}
