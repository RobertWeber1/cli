#include "buffer.h"
#include <iostream>

namespace CLI
{

namespace border
{

const util::Size Buffer::DefaultMaxSize(5000, 5000);

Buffer::Buffer( util::Size const& size, util::Size const& max_size )
: _max_size(max_size)
, _elements(NULL)
{
	resize(size);
}


Buffer::~Buffer()
{
	delete_elements();
}


void Buffer::resize( util::Size const& size )
{
	delete_elements();
	_current_size = size.trim(_max_size);
	_elements = new Element[ _current_size.width() * _current_size.height() ];
}


util::Size const& Buffer::size() const
{
	return _current_size;
}

void Buffer::draw( util::Point const& top_left, util::Size const& size, Operation operation, InvertDrawing inverted )
{
	Element::Type inv = (inverted == DrawInverted) ? Element::INVERT : Element::NONE;

	util::Point p1( top_left );
	util::Point p2( top_left.x(), top_left.y() + size.height() - 1 );

	set( p1, operation, Element::TOP_LEFT, inv );
	set( p2, operation, Element::BOTTOM_LEFT, inv );

	for( size_t i = 0; (i < size.width()-2 and i < _current_size.width() ); ++i )
	{
		p1.right();
		p2.right();
		set( p1, operation, Element::HORIZONTAL, inv );
		set( p2, operation, Element::HORIZONTAL, inv );
	}

	p1.right();
	p2.right();
	set( p1, operation, Element::TOP_RIGHT, inv );
	set( p2, operation, Element::BOTTOM_RIGHT, inv );

	p1.set(top_left.x(), top_left.y() + 1);
	p2.set(top_left.x() + size.width() -1, top_left.y() + 1);

	for( size_t i = 0; (i < size.height()-2 and i < _current_size.height() ); ++i )
	{
		set( p1, operation, Element::VERTICAL, inv );
		set( p2, operation, Element::VERTICAL, inv );
		p1.down();
		p2.down();
	}
}


Element* Buffer::get( util::Point const& position )
{
	if( position.x() >= _current_size.width() or
	    position.y() >= _current_size.height() )
	{
		return NULL;
	}
	return &_elements[ position.x() + (position.y()*_current_size.width()) ];
}


void Buffer::set( util::Point const& point, Operation operation, Element::Type type, Element::Type inverted )
{
	Element * element = NULL;
	if( (element = get(point)) != NULL )
	{
		if(operation == Add)
		{
			element->add(type).add(inverted);
		}
		else
		{
 			element->remove(type).remove(inverted);
		}
	}
}

void Buffer::delete_elements()
{
	if(_elements != NULL)
	{
		delete[] _elements;
		_elements = NULL;
		_current_size.zero();
	}
}



} //namespace border

} //namespace CLI
