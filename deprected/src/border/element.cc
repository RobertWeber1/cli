#include "element.h"
#include <iostream>

namespace CLI
{

namespace border
{


uint8_t toBit( const Element::Type & type, uint8_t bit )
{
	return (static_cast<uint8_t>(type) >> bit) & 0x01;
}


uint8_t toBit( uint8_t type, uint8_t bit )
{
	return (type >> bit) & 0x01;
}


Element::Element( Type type )
: top_counter( toBit(type,0) )
, right_counter( toBit(type,1) )
, bottom_counter( toBit(type,2) )
, left_counter( toBit(type,3) )
, invert_counter( toBit(type,4) )
{}


Element::Element( uint8_t type )
: top_counter( toBit(type,0) )
, right_counter( toBit(type,1) )
, bottom_counter( toBit(type,2) )
, left_counter( toBit(type,3) )
, invert_counter( toBit(type,4) )
{}


Element& Element::add( const Element& c )
{
	top_counter += c.top_counter;
	right_counter += c.right_counter;
	bottom_counter += c.bottom_counter;
	left_counter += c.left_counter;
	invert_counter += c.invert_counter;
	return *this;
}


Element& Element::remove( const Element& c )
{
	top_counter -= c.top_counter;
	right_counter -= c.right_counter;
	bottom_counter -= c.bottom_counter;
	left_counter -= c.left_counter;
	invert_counter -= c.invert_counter;
	return *this;
}


Element& Element::set(const Element& c)
{
	top_counter = c.top_counter;
	right_counter = c.right_counter;
	bottom_counter = c.bottom_counter;
	left_counter = c.left_counter;
	invert_counter = c.invert_counter;
	return *this;
}


Element& Element::add(const Type& type)
{
	top_counter += toBit(type, 0);
	right_counter += toBit(type, 1);
	bottom_counter += toBit(type, 2);
	left_counter += toBit(type, 3);
	invert_counter += toBit(type, 4);
	return *this;
}


Element& Element::remove(const Type& Type)
{
	top_counter -= toBit(Type, 0);
	right_counter -= toBit(Type, 1);
	bottom_counter -= toBit(Type, 2);
	left_counter -= toBit(Type, 3);
	invert_counter -= toBit(Type, 4);
	return *this;
}


Element& Element::set(const Type& Type)
{
	top_counter = toBit(Type, 0);
	right_counter = toBit(Type, 1);
	bottom_counter = toBit(Type, 2);
	left_counter = toBit(Type, 3);
	invert_counter = toBit(Type, 4);
	return *this;
}


void Element::invert(bool value)
{
	invert_counter += (value ? 1 : -1);
}


bool Element::is_none() const
{
	return ( top_counter +
	         right_counter +
	         bottom_counter +
	         left_counter == 0 ) ? true : false;
}


bool Element::is_inverted() const
{
	return (( invert_counter != 0 ) ? true : false );
}


uint8_t Element::index() const
{
	return ( top_counter    ? 1 : 0 ) |
	       ( right_counter  ? 2 : 0 ) |
	       ( bottom_counter ? 4 : 0 ) |
	       ( left_counter   ? 8 : 0 );
}


Element::Type Element::type() const
{
	return static_cast<Type>(index());
}


char Element::to_char( char char_table[16] ) const
{
	return char_table[index()];
}


} //namespace border

} //namespace CLI
