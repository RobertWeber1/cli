#include "layout.h"


Layout::~Layout()
{
}


void Layout::addObject(LayoutObject * object)
{
	objects.push_back(object);
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
