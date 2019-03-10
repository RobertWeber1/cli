#pragma once
#include "properties.h"
#include "permanence.h"

#include <string>


namespace CLI
{

namespace util
{

class StreamCommand
{
public:
	enum Id
	{
		ForegroundColor = 1,
		BackgroundColor,
		TextAttribure,
		TextAlignment,
		PermanetFlag
	};

	static const std::string ESCAPE;

	StreamCommand( Properties const& prop = Properties(), Permanece perm = OneLine );

	void deserialize( std::string const& data );

	std::string serialize() const;

	static  std::string serialize( Id cmd );

	static Id to_id( char c );

	static std::string serialize( Color color );

	static Color to_color( char c );

	static std::string serialize( Alignment align );

	static Alignment to_align( char c );

	static std::string serialize( Attribute attr );

	static Attribute to_attr( char c );

	static std::string serialize( Permanece perm );

	static Permanece to_perm( char c);

	Properties _properties;
	Permanece  _permnence;
};


} //namespace util

} //namespace CLI
