#pragma once
#include "layout_object.h"
#include "layout.h"
#include "border/buffer.h"

namespace CLI
{

namespace layout
{


class VerticalLayout : public LayoutObject, public Layout
{
public:
	VerticalLayout( const util::SizeHint & size_hint = util::SizeHint() );

	virtual ~VerticalLayout();

	//LayoutObject
	void size( util::Point const& position, util::Size const& size );

	void border_to_buffer( border::Buffer& buffer );

private:
	//LayoutObject
	util::SizeHint calc_size_hint();
};


}// namespace layout

} // namespace CLI
