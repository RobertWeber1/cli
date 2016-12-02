#include "layout.h"
#include "hlayout.h"
#include "vlayout.h"

Layout::~Layout()
{
}


void Layout::addObject(LayoutObject * object, InsertPosition pos)
{
	switch(pos)
	{
	case FRONT:
		objects.insert(objects.begin(), object);
		break;

	case CENTER:
		objects.insert(objects.begin()+objects.size()/2, object);
		break;

	case BACK:
	default:
		objects.push_back(object);
		break;
	}
}


void Layout::removeObject(LayoutObject * object)
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
				static_cast<HLayout*>(*it)->removeObject(object);
				break;
			case LayoutObject::V_LAYOUT:
				static_cast<VLayout*>(*it)->removeObject(object);
				break;
			default:
				break;
			}
		}
	}
}
