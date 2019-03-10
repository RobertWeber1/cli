#include "stream_command.h"


namespace CLI
{

namespace util
{

const std::string StreamCommand::ESCAPE = "\033";

StreamCommand::StreamCommand( Properties const& prop, Permanece perm )
: _properties( prop )
, _permnence( perm )
{}


void StreamCommand::deserialize( std::string const& data )
{
	const char* p = data.c_str();

	if( *p == '\033' )
	{
		p++;
	}

	for( int i=0; i<5; ++i)
	{
		switch( to_id( *p++ ) )
		{
		case ForegroundColor:
			_properties.foreground = to_color( *p );
			break;

		case BackgroundColor:
			_properties.background = to_color( *p );
			break;

		case TextAttribure:
			_properties.attribute = to_attr( *p );
			break;

		case TextAlignment:
			_properties.alignment = to_align( *p );
			break;

		case PermanetFlag:
			_permnence = to_perm( *p );
			break;

		default:
			break;
		}

		p++;
	}

}


std::string StreamCommand::serialize() const
{
	return ESCAPE +
	       serialize( ForegroundColor ) + serialize( _properties.foreground ) +
	       serialize( BackgroundColor ) + serialize( _properties.background ) +
	       serialize( TextAttribure ) + serialize( _properties.attribute ) +
	       serialize( TextAlignment ) + serialize( _properties.alignment ) +
	       serialize( PermanetFlag ) + serialize( _permnence );
}


std::string StreamCommand::serialize( Id cmd )
{
	return std::string( reinterpret_cast<char*>(&cmd), 1 );
}


StreamCommand::Id StreamCommand::to_id( char c )
{
	return static_cast<Id>(c);
}


std::string StreamCommand::serialize( Color color )
{
	return std::string( reinterpret_cast<char*>( &color ), 1 );
}


Color StreamCommand::to_color( char c )
{
	return static_cast<Color>(c);
}


std::string StreamCommand::serialize( Alignment align )
{
	return std::string( reinterpret_cast<char*>( &align ), 1 );
}


Alignment StreamCommand::to_align( char c )
{
	return static_cast<Alignment>(c);
}


std::string StreamCommand::serialize( Attribute attr )
{
	return std::string( reinterpret_cast<char*>( &attr ), 1 );
}


Attribute StreamCommand::to_attr( char c )
{
	return static_cast<Attribute>(c);
}


std::string StreamCommand::serialize( Permanece perm )
{
	return std::string( reinterpret_cast<char*>( &perm ), 1 );
}


Permanece StreamCommand::to_perm( char c)
{
	return static_cast<Permanece>(c);
}


} //namespace util

} //namespace CLI
