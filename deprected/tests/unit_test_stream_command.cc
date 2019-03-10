#include "catch.h"
#include "util/stream_command.h"


TEST_CASE( "serialize StreamCommand" )
{
	char expected[] = { '\033', '\x01', '\x02', '\x02', '\x01', '\x03', '\x01', '\x04', '\x01', '\x05', '\x02' };
	CLI::util::StreamCommand cmd( CLI::util::Properties(), CLI::util::AllLines );

	REQUIRE( cmd.serialize() == std::string( (char*)&expected, 11 ) );
}


TEST_CASE( "deserialize StreamCommand" )
{
	char expected[] = { '\033', '\x01', '\x04', '\x02', '\x05', '\x03', '\x05', '\x04', '\x02', '\x05', '\x02' };
	CLI::util::StreamCommand cmd( CLI::util::Properties(), CLI::util::AllLines );

	cmd.deserialize( std::string( (char*)&expected, 11 ) );

	REQUIRE( cmd._properties.foreground == CLI::util::GREEN );
	REQUIRE( cmd._properties.background == CLI::util::BLUE );
	REQUIRE( cmd._properties.attribute == CLI::util::BLINK );
	REQUIRE( cmd._properties.alignment == CLI::util::CENTER );
	REQUIRE( cmd._permnence == CLI::util::AllLines );
}