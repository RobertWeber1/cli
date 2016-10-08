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

protected:
	std::vector<LayoutObject*> objects;

public:
	Layout() {};
	virtual ~Layout();

	virtual void addObject(LayoutObject * object);
	virtual void removeObject(LayoutObject * object);
	//virtual Position getRelativPosition(LayoutObject * object);
};
