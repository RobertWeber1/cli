#pragma once
#include "layoutobject.h"
#include <vector>


class Layout
{
public:
	typedef struct Position{
		unsigned int x;
		unsigned int y;
		Position(unsigned int x, unsigned int y) : x(x), y(y) {}
	}Position;

	typedef enum InsertPosition 
	{
		FRONT,
		CENTER,
		BACK,
	}InsertPosition;

protected:
	std::vector<LayoutObject*> objects;

public:
	Layout() {};
	virtual ~Layout();

	virtual void addObject(LayoutObject * object, InsertPosition pos = BACK);
	virtual void removeObject(LayoutObject * object);
	//virtual Position getRelativPosition(LayoutObject * object);
};
