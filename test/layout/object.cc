#include "catch.h"
#include <cli/layout/object.h>
#include <cli/layout/size_hint.h>


using namespace cli::layout;

using o1 = Object<WidthHint<1,10,2>, HeightHint<3,30,3>>;
using o2 = Object<WidthHint<2,20,2>, HeightHint<2,20,3>>;
using o3 = Object<WidthHint<3,30,2>, HeightHint<1,10,3>>;


TEST_CASE("AddHints")
{
	REQUIRE(get_min(AddHints<WidthHint, o1, o2, o3>::type{}) == cli::Width(6));
	REQUIRE(get_max(AddHints<WidthHint, o1, o2, o3>::type{}) == cli::Width(60));
	REQUIRE(get_factor(AddHints<WidthHint, o1, o2, o3>::type{}) == 6);

	REQUIRE(get_min(AddHints<HeightHint, o1, o2, o3>::type{}) == cli::Height(6));
	REQUIRE(get_max(AddHints<HeightHint, o1, o2, o3>::type{}) == cli::Height(60));
	REQUIRE(get_factor(AddHints<HeightHint, o1, o2, o3>::type{}) == 9);
}


TEST_CASE("MaxHints")
{
	REQUIRE(get_min(MaxHints<WidthHint, o1, o2, o3>::type{}) == cli::Width(3));
	REQUIRE(get_max(MaxHints<WidthHint, o1, o2, o3>::type{}) == cli::Width(30));
	REQUIRE(get_factor(MaxHints<WidthHint, o1, o2, o3>::type{}) == 2);

	REQUIRE(get_min(MaxHints<HeightHint, o1, o2, o3>::type{}) == cli::Height(3));
	REQUIRE(get_max(MaxHints<HeightHint, o1, o2, o3>::type{}) == cli::Height(30));
	REQUIRE(get_factor(MaxHints<HeightHint, o1, o2, o3>::type{}) == 3);
}