#pragma once
#include "layout_object.h"
#include <vector>

namespace CLI
{

namespace layout
{


class Layout
{
public:
	Layout() {}
	virtual ~Layout() {}

	virtual void add( LayoutObject * object );
	virtual void remove( LayoutObject * object );

protected:
	std::vector<LayoutObject*> objects;
};


} //namespace layout

} //namespace CLI
