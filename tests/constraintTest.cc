#include "layoutobject.h"
#include <iostream>

int main(int argc, char* argv[])
{
	int result = 0;

	LayoutObject::SizeConstraint defaultConstraint;
	LayoutObject::SizeConstraint c1(3, 10, 2);

	std::cout << "defaultConstraint: " << defaultConstraint << std::endl;
	std::cout << "c1:                " << c1 << std::endl;

	LayoutObject::SizeConstraint summe(0, 0, 0);
	LayoutObject::SizeConstraint maximum(0, 0, 0);

	summe.add(defaultConstraint);
	summe.add(c1);

	maximum.max(defaultConstraint);
	maximum.max(c1);

	std::cout << "summe:             " << summe << std::endl;
	std::cout << "maimum:            " << maximum << std::endl;

	return result;
}
