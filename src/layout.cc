#include "layout.h"


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
	}
}
