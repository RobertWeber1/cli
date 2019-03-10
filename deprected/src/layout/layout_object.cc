#include "layout_object.h"

namespace CLI
{

namespace layout
{


LayoutObject::LayoutObject( util::SizeHint const& sizeHint, ObjectType type )
: type( type )
, _size( 3, 3 )
, _default_size_hint( sizeHint )
{}


util::Size const& LayoutObject::size() const
{
	return _size;
}


util::Size & LayoutObject::size()
{
	return _size;
}


util::SizeHint const& LayoutObject::size_hint()
{
	_size_hint = calc_size_hint();
	return _size_hint;
}


} //namespace layout

} //namespace CLI
