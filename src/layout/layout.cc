#include "layout.h"
#include "vertical_layout.h"

namespace CLI
{

namespace layout
{


void Layout::add(LayoutObject * object)
{
	objects.push_back(object);
}


void Layout::remove(LayoutObject * object)
{
	for(std::vector<LayoutObject*>::iterator it = objects.begin(); it != objects.end(); it++)
	{
		if((*it) == object)
		{
			objects.erase(it);
			break;
		}
		else
		{
			switch((*it)->type)
			{
			case LayoutObject::H_LAYOUT:
				//static_cast<HLayout*>(*it)->removeObject(object);
				break;
			case LayoutObject::V_LAYOUT:
				static_cast<VerticalLayout*>(*it)->remove(object);
				break;
			default:
				break;
			}
		}
	}
}


} //namespace layout

} //namespace CLI
