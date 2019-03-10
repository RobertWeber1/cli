#pragma once
#include "layout_object.h"
#include "layout.h"
#include "border/buffer.h"

namespace CLI
{

namespace layout
{


class HorizontalLayout : public LayoutObject, public Layout
{
public:
	HorizontalLayout( const util::SizeHint & size_hint = util::SizeHint() );

	virtual ~HorizontalLayout();

	//LayoutObject
	void size( util::Point const& position, util::Size const& size );

	void border_to_buffer( border::Buffer& buffer );

private:
	//LayoutObject
	util::SizeHint calc_size_hint();
};


}// namespace layout

} // namespace CLI
