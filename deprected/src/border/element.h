#pragma once
#include <stdint.h>
#include <ostream>

namespace CLI
{

namespace border
{

class Element
{
public:
	//     2^1
	//      |
	//2^4 -- -- 2^2
	//      |
	//     2^3
	typedef enum Type
	{
		NONE         = 0b00000,
		UNUSED_1     = 0b00001,
		UNUSED_2     = 0b00010,
		BOTTOM_LEFT  = 0b00011,
		UNUSED_4     = 0b00100,
		VERTICAL     = 0b00101,
		TOP_LEFT     = 0b00110,
		TEE_RIGHT    = 0b00111,
		UNUSED_8     = 0b01000,
		BOTTOM_RIGHT = 0b01001,
		HORIZONTAL   = 0b01010,
		TEE_TOP      = 0b01011,
		TOP_RIGHT    = 0b01100,
		TEE_LEFT     = 0b01101,
		TEE_BOTTOM   = 0b01110,
		CROSS        = 0b01111,
		INVERT       = 0b10000
	}Type;


	Element( Type type = NONE );
	Element( uint8_t type );

	Element& add( const Element& border_char );
	Element& remove( const Element& border_char );
	Element& set( const Element& border_char );
	Element& add( const Type& border_type );
	Element& remove( const Type& border_type );
	Element& set( const Type& border_type );
	void invert(bool value = true);

	bool is_none() const;
	bool is_inverted() const;
	uint8_t index() const;
	Type type() const;
	char to_char( char char_table[16] ) const;


	uint8_t invert_counter;
	uint8_t top_counter;
	uint8_t right_counter;
	uint8_t bottom_counter;
	uint8_t left_counter;
};

} //namespace border

} //namespace CLI
