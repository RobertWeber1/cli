#pragma once
#include "element.h"
#include "util/size.h"
#include "util/point.h"

namespace CLI
{

namespace border
{


class Buffer
{
public:
	typedef enum InvertDrawing
	{
		DrawNormal,
		DrawInverted
	}InvertDrawing;

	typedef enum Operation
	{
		Add,
		Remove
	}Operation;

	static const util::Size DefaultMaxSize;

	Buffer( util::Size const& size, util::Size const& max_size = DefaultMaxSize );
	virtual ~Buffer();

	void resize( util::Size const& size );
	util::Size const& size() const;

	void draw( util::Point const& top_left, util::Size const& size, Operation operation = Add, InvertDrawing inverted = DrawNormal );
	// void invert( util::Point const& top_left, util::Size const& size, bool inverted );
	// void remove( util::Point const& top_left, util::Size const& size, bool inverted = false );

	Element* get( util::Point const& position );

private:

	void set( util::Point const& point, Operation operation, Element::Type type, Element::Type inverted = Element::NONE );
	void delete_elements();

	util::Size _current_size;
	util::Size _max_size;
	Element  * _elements;
};


} //namespace border

} //namespace CLI
