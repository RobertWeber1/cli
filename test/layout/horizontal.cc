#include "../catch.h"
#include <cli/layout/horizontal.h>


using namespace cli::layout;

using o1 = Object<WidthHint<1,10,2>, HeightHint<3,30,3>>;
using o2 = Object<WidthHint<2,20,2>, HeightHint<2,20,3>>;
using o3 = Object<WidthHint<3,30,2>, HeightHint<1,10,3>>;
using h1 = Horizontal<o1, o2, o3>;

TEST_CASE("Simple horizontal layout")
{
	REQUIRE(get_min(get_hint<WidthHint, h1>::type{}) == cli::Width(6));
	REQUIRE(get_max(get_hint<WidthHint, h1>::type{}) == cli::Width(60));
	REQUIRE(get_factor(get_hint<WidthHint, h1>::type{}) == 6);

	REQUIRE(get_min(get_hint<HeightHint, h1>::type{}) == cli::Height(3));
	REQUIRE(get_max(get_hint<HeightHint, h1>::type{}) == cli::Height(30));
	REQUIRE(get_factor(get_hint<HeightHint, h1>::type{}) == 3);
}


TEST_CASE("Nested horizontal layout")
{
	using h2 = Horizontal<h1, o1, o2, o3>;

	REQUIRE(get_min(get_hint<WidthHint, h2>::type{}) == cli::Width(12));
	REQUIRE(get_max(get_hint<WidthHint, h2>::type{}) == cli::Width(120));
	REQUIRE(get_factor(get_hint<WidthHint, h2>::type{}) == 12);

	REQUIRE(get_min(get_hint<HeightHint, h2>::type{}) == cli::Height(3));
	REQUIRE(get_max(get_hint<HeightHint, h2>::type{}) == cli::Height(30));
	REQUIRE(get_factor(get_hint<HeightHint, h2>::type{}) == 3);
}
