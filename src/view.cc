#include "view.h"
#include "hlayout.h"
#include "vlayout.h"
#include "cliwindow.h"
#include <stdarg.h>

UnknownLayoutException::UnknownLayoutException(const std::string& viewName, 
                                               const std::string& layoutName) throw():
	viewName(viewName), layoutName(layoutName)
{
	fillWhat();
}

UnknownLayoutException::UnknownLayoutException(const UnknownLayoutException & e) throw() :
	viewName(e.viewName), layoutName(e.layoutName)
{
	fillWhat();
}

void UnknownLayoutException::fillWhat()
{
	whatStr << "The layout name \"" << layoutName 
	        << "\" is unknown in view \""  << viewName << "\"";
}

const char* UnknownLayoutException::what() const throw()
{
	return (whatStr.str().c_str());
}


//----------------------------------------------------------------------------//


NameDuplicateException::NameDuplicateException(const std::string& viewName,
                                               const std::string& objectName,
                                               LayoutObject::ObjectType type) throw():
	viewName(viewName), objectName(objectName), type(type)
{
	fillWhat();
}

NameDuplicateException::NameDuplicateException(const NameDuplicateException & e) throw():
	viewName(e.viewName), type(e.type), objectName(e.objectName)
{
	fillWhat();
}

void NameDuplicateException::fillWhat()
{
	whatStr << "The "<< ((type==LayoutObject::WINDOW)?"window":"layout") <<" name \"" << objectName 
	        << "\" is aleary used in view \"" << viewName << "\"";
}

const char* NameDuplicateException::what() const throw()
{
	return whatStr.str().c_str();
}


//----------------------------------------------------------------------------//


ParentIsWindowException::ParentIsWindowException(const std::string& viewName, 
                                                 const std::string& windowName,
                                                 const std::string& layoutObjectName) throw():
	viewName(viewName), windowName(windowName), layoutObjectName(layoutObjectName)
{
	fillWhat();
}

ParentIsWindowException::ParentIsWindowException(const ParentIsWindowException & e) throw():
	viewName(e.viewName), windowName(e.windowName), layoutObjectName(e.layoutObjectName)
{
	fillWhat();
}

void ParentIsWindowException::fillWhat()
{
	whatStr << "You tried to insert a LayoutObject(" << layoutObjectName 
	        << ") into a Window (" << windowName <<"in view " << viewName << ")";
}

const char* ParentIsWindowException::what() const throw()
{
	return whatStr.str().c_str();
}


//----------------------------------------------------------------------------//


UnknownLayoutTypeException::UnknownLayoutTypeException(const std::string& viewName, 
                                                       const std::string& layoutName,
                                                       LayoutObject::ObjectType type) throw():
	viewName(viewName), layoutName(layoutName), type(type)
{
	fillWhat();
}

UnknownLayoutTypeException::UnknownLayoutTypeException(const UnknownLayoutTypeException & e) throw():
	viewName(e.viewName), layoutName(e.layoutName), type(e.type)
{
	fillWhat();
}

void UnknownLayoutTypeException::fillWhat()
{
	whatStr << "The layout type \"" << static_cast<int>(type) << "\" (" 
	        << LayoutObject::ObjectTypeName[static_cast<int>(type)] << ") is unknown " 
	        << "(view name: " << viewName << ", layout name: " << layoutName << ")!";
}

const char* UnknownLayoutTypeException::what() const throw()
{
	return whatStr.str().c_str();
}


//----------------------------------------------------------------------------//


View::View(const std::string & name) :
	name(name), rootObject(NULL), borderBuffer()
{}


View::~View()
{

	for(std::map<std::string, LayoutObject*>::iterator it = layoutMap.begin(); it != layoutMap.end(); it++)
	{
		delete it->second;
	}

	for(std::map<std::string, CLIWindow*>::iterator it =  windowMap.begin(); it != windowMap.end(); it++)
	{
		delete it->second;
	}
}


LayoutObject * View::createObj(LayoutObject::ObjectType type, const std::string& objectName)
{
	LayoutObject* obj = NULL;
	std::pair<std::map<std::string, LayoutObject*>::iterator, bool> insertLResult;
	std::pair<std::map<std::string, CLIWindow*>::iterator, bool> insertWResult;

	switch(type)
	{
		case LayoutObject::H_LAYOUT:
			obj = new HLayout();
			insertLResult = layoutMap.insert(make_pair(objectName, obj));
			if(!insertLResult.second)
			{
				delete obj;
				obj = NULL;
			}
		break;

		case LayoutObject::V_LAYOUT:
			obj = new VLayout();
			insertLResult = layoutMap.insert(make_pair(objectName, obj));
			if(!insertLResult.second)
			{
				delete obj;
				obj = NULL;
			}
		break;

		case LayoutObject::WINDOW:
			obj = new CLIWindow();
			insertWResult = windowMap.insert(make_pair(objectName, static_cast<CLIWindow*>(obj)));
			if(!insertWResult.second)
			{
				delete obj;
				obj = NULL;
			}
		break;
	}
	
	return obj;
}


void addObjToObj(LayoutObject * child, LayoutObject * parent)
{
	switch(parent->type)
	{
	case LayoutObject::H_LAYOUT:
		static_cast<HLayout*>(parent)->addObject(child);
		break;
	case LayoutObject::V_LAYOUT:
		static_cast<VLayout*>(parent)->addObject(child);
		break;
	}
}

void removeObjFromObj(LayoutObject * child, LayoutObject * parent)
{
	switch(parent->type)
	{
	case LayoutObject::H_LAYOUT:
		static_cast<HLayout*>(parent)->removeObject(child);
		break;
	case LayoutObject::V_LAYOUT:
		static_cast<VLayout*>(parent)->removeObject(child);
		break;
	}
}

void View::addLayout(LayoutObject::ObjectType type,
                     const std::string & layoutName,
                     const std::string & parentName)
{

	if(windowMap.find(layoutName) != windowMap.end() || 
	   layoutMap.find(layoutName) != layoutMap.end())
	{
		throw NameDuplicateException(name, layoutName, type);
	}

	if(type != LayoutObject::H_LAYOUT && type != LayoutObject::V_LAYOUT)
	{
		throw UnknownLayoutTypeException(name, layoutName, type);
	}

	if(parentName != "")
	{
	 	std::map<std::string, LayoutObject*>::iterator findResult;
	 	findResult = layoutMap.find(parentName);
	 	if(findResult == layoutMap.end())
	 	{
	 		throw UnknownLayoutException(name, layoutName);
	 	}
	 	else
	 	{
			addObjToObj(createObj(type, layoutName), findResult->second);
	 	}
	}
	else
	{
		if(rootObject)
		{
			if(rootObject->type == LayoutObject::H_LAYOUT || 
			   rootObject->type == LayoutObject::V_LAYOUT)
			{
				addObjToObj(createObj(type, layoutName), rootObject);					
			}	
			else
			{
				throw ParentIsWindowException(name, parentName, layoutName);
			}
		}
		else
		{
			rootObject = createObj(type, layoutName);
		}
	}	
}


CLIWindow * View::addWindow(const std::string & windowName, const std::string & parentName)
{
	if(windowMap.find(windowName) != windowMap.end() || 
	   layoutMap.find(windowName) != layoutMap.end())
	{
		throw NameDuplicateException(name, windowName);
	}

	if(parentName == "")
	{
		if(rootObject != NULL)
		{
			if(rootObject->type == LayoutObject::WINDOW)
			{
				throw ParentIsWindowException(name, "", windowName);
			}
			else
			{
				addObjToObj(createObj(LayoutObject::WINDOW, windowName), rootObject);
			}
		}
		else
		{
			rootObject = createObj(LayoutObject::WINDOW, windowName);
		}
	}
	else
	{
		std::map<std::string, LayoutObject*>::iterator findResult;
	 	findResult = layoutMap.find(parentName);
	 	if(findResult == layoutMap.end())
	 	{
	 		throw UnknownLayoutException(name, windowName);
	 	}
	 	else
	 	{
	 		addObjToObj(createObj(LayoutObject::WINDOW, windowName), findResult->second);
	 	}
	}
}




void View::removeObject(const std::string & name)
{
	LayoutObject * findResult = NULL; 
	std::map<std::string, LayoutObject*>::iterator layoutFindResult;
	std::map<std::string, CLIWindow*>::iterator windowFindResult;


	layoutFindResult = layoutMap.find(name);
	if(layoutFindResult == layoutMap.end())
	{
		windowFindResult = windowMap.find(name);
		if(windowFindResult == windowMap.end())
		{
			findResult = windowFindResult->second;
			windowMap.erase(windowFindResult);
		}
		else
		{
			return;
		}
	}
	else
	{
		findResult = layoutFindResult->second;
		layoutMap.erase(layoutFindResult);
	}

	if(findResult)
	{
		removeObjFromObj(findResult, rootObject);
		delete findResult;
	}
}


LayoutObject * View::getRoot()
{
	return rootObject;
}
