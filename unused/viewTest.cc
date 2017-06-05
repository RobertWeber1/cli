#include "view.h"
#include <iostream>
#include <assert.h>
#include <string>
#include <vector>



int main(int argc, char *argv[])
{
	View view1("testView");

	std::cout << "add root layout" << std::endl;
	view1.addLayout(LayoutObject::H_LAYOUT, "root", "");
	std::cout << "add h1 to root" << std::endl;
	view1.addLayout(LayoutObject::H_LAYOUT, "h1", "root");
	std::cout << "add h2 to h1" << std::endl;
	view1.addLayout(LayoutObject::H_LAYOUT, "h2", "h1");

	std::cout << "----------- end --------------" << std::endl;


	// std::cout << "try to add root layout a second time" << std::endl;
	// try
	// {
	// 	view1.addLayout(LayoutObject::H_LAYOUT, "root", "");
	// } 
	// catch (NameDuplicateException & e)
	// {
	// 	std::cout << e.what() << std::endl;
	// }

	// std::cout << "try to add WINDOW as layout" << std::endl;
	// try
	// {
	// 	view1.addLayout(LayoutObject::WINDOW, "w1", "");
	// } 
	// catch (UnknownLayoutTypeException & e)
	// {
	// 	std::cout << e.what() << std::endl;
	// }




	//view1.addLayoutObjects("root:H_LAYOUT", "foo:WINDOW:data1", "bar:V_LAYOUT", NULL);
	
	return 0;
}