#include "catch.h"
#include <cli/layout/size_hint.h>
#include <type_traits>


using namespace cli::layout;


TEST_CASE("get values")
{
	WidthHint<2, 6> w1;

	REQUIRE(get_min(w1) == cli::Width{2});
	REQUIRE(get_max(w1) == cli::Width{6});
	REQUIRE(get_factor(w1) == 1);
}



// TEST_CASE("Add")
// {
// 	using w1 = WidthHint<2, 6>;
// 	using w2 = WidthHint<6, 12, 5>;

// 	using w12 = Add<w1, w2>::type;

// 	REQUIRE(get_min(w12{}) == cli::Width{8});
// 	REQUIRE(get_max(w12{}) == cli::Width{18});
// 	REQUIRE(get_factor(w12{}) == 6);


// 	using h1 = HeightHint<2, 6>;
// 	using h2 = HeightHint<6, 12, 5>;

// 	using h12 = Add<h1, h2>::type;

// 	REQUIRE(get_min(h12{}) == cli::Height{8});
// 	REQUIRE(get_max(h12{}) == cli::Height{18});
// 	REQUIRE(get_factor(h12{}) == 6);
// }



// TEST_CASE("Max")
// {
// 	using w1 = WidthHint<2, 16>;
// 	using w2 = WidthHint<6, 12, 5>;

// 	using w12 = Max<w1, w2>::type;

// 	REQUIRE(get_min(w12{}) == cli::Width{6});
// 	REQUIRE(get_max(w12{}) == cli::Width{16});
// 	REQUIRE(get_factor(w12{}) == 5);


// 	using h1 = HeightHint<2, 16>;
// 	using h2 = HeightHint<6, 12, 5>;

// 	using h12 = Max<h1, h2>::type;

// 	REQUIRE(get_min(h12{}) == cli::Height{6});
// 	REQUIRE(get_max(h12{}) == cli::Height{16});
// 	REQUIRE(get_factor(h12{}) == 5);
// }