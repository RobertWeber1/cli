#include "view.h"

std::string name;
	LayoutObject *rootObject;
	std::map<std::string, LayoutObject*> layoutMap;
	std::map<std::string, CLIWindowi*> windowMap;
	BorderBuffer borderBuffer;


View::View(const std::string & name) :
	name(name), rootObject(NULL), borderBuffer()
{}


View::~View()
{
	for(std::map<std::string, LayoutObject*>::iterator it = layoutMap.begin(); it != layoutMap.end(); it++)
	{
		delete it->second;
	}

	for(std::map<std::string, CLIWindowi*>::iterator it =  windowMap.begin(); it != windowMap.end(); it++)
	{
		delete it->second;
	}
}


void View::addLayout(LayoutType type, const std::string & layoutName, const std::string & parentName = "")
{
	
}


CLIWindow * View::addWindow(const std::string & WindowName, const std::string & parentName = "")
{

}


void View::removeObject(const std::string & name)
{

}


void View::resize(unsigned int width, unsigned int height)
{

}


void View::printContent()
{

}


void View::printBorder()
{

}

