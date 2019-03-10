#include <cli/version.h>
#include "catch.h"

TEST_CASE("version")
{
	REQUIRE(cli::Version::project_name == "libcli");
	REQUIRE(cli::Version::git_tag != "");
	REQUIRE(cli::Version::build_date != "");
}
