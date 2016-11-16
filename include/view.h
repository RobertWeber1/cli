#pragma once

#include "layoutobject.h"
#include "cliwindow.h"
#include <map>
#include <string>
#include <exception> 

class UnknownLayoutException : public std::exception
{

}

class NameDuplicateException : public std::exception
{

}

class ParentIsWindowException : public std::exception
{
	
}

class View
{
private:
	std::string name;
	LayoutObject *rootObject;
	std::map<std::string, LayoutObject*> layoutMap;
	std::map<std::string, CLIWindowi*> windowMap;
	BorderBuffer borderBuffer;

public:
	View(const std::string & name);
	~View();

	void addLayout(LayoutType type, const std::string & layoutName, const std::string & parentName = "");
	CLIWindow * addWindow(const std::string & WindowName, const std::string & parentName = "");
	void removeObject(const std::string & name);
	
	void resize(unsigned int width, unsigned int height);
	void printContent();
	void printBorder();
}