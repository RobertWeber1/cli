#include <cli/types.h>
#include "catch.h"


using Coll_t = cli::Collumn<uint8_t>;
using CollDist_t = cli::ColDistance<uint8_t>;


TEST_CASE("Collumn")
{
	SECTION("equality comparison")
	{
		REQUIRE(Coll_t{5} == Coll_t{5});
		REQUIRE(Coll_t{5} != Coll_t{6});
	}

	SECTION("assignment")
	{
		Coll_t col{5};

		REQUIRE(col == Coll_t{5});

		col = Coll_t{6};

		REQUIRE(col == Coll_t{6});
	}
}

TEST_CASE("CollumnDistance")
{
	SECTION("equality comparison")
	{
		REQUIRE(CollDist_t{5} == CollDist_t{5});
		REQUIRE(CollDist_t{5} != CollDist_t{6});
	}

	SECTION("assignment")
	{
		CollDist_t dist{5};

		REQUIRE(dist == CollDist_t{5});

		dist = CollDist_t{6};

		REQUIRE(dist == CollDist_t{6});
	}
}


TEST_CASE("add/subtract collumn and distance")
{
	REQUIRE(Coll_t{5} + CollDist_t{6} == Coll_t{11});
	REQUIRE(CollDist_t{8} + Coll_t{21}  == Coll_t{29});

	REQUIRE(Coll_t{10} - CollDist_t{6} == Coll_t{4});
}


TEST_CASE("subtract collumns get distance")
{
	REQUIRE(Coll_t{5} - Coll_t{3} == CollDist_t{2});
	REQUIRE(Coll_t{3} - Coll_t{5} == CollDist_t{254});
}


TEST_CASE("scale distance")
{
	REQUIRE(CollDist_t{2} * 5 == CollDist_t{10});
	REQUIRE(CollDist_t{10} / 2 == CollDist_t{5});
	REQUIRE(CollDist_t{10} % 7 == CollDist_t{3});
}

