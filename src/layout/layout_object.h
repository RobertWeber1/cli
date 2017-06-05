#pragma once
#include "util/size_hint.h"
#include "util/size.h"
#include "util/point.h"
#include "border/buffer.h"

namespace CLI
{

namespace layout
{


class LayoutObject
{
public:
	typedef enum ObjectType
	{
		NONE = 0,
		WIDGET,
		H_LAYOUT,
		V_LAYOUT
	}ObjectType;

	LayoutObject( util::SizeHint const& sizeHint, ObjectType type );

	virtual ~LayoutObject() {}

	util::Size const& size() const;

	util::Size & size();

	util::SizeHint const& size_hint();

	virtual void size( util::Point const& position, util::Size const& size ) = 0;

	virtual void border_to_buffer( border::Buffer& buffer ) = 0;

	const ObjectType type;

protected:
	util::Size _size;
	util::SizeHint _default_size_hint;
	util::SizeHint _size_hint;

	virtual util::SizeHint calc_size_hint() = 0;
};


} //namespace layout

} //namespace CLI
