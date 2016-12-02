#pragma once

#include "layoutobject.h"
#include "cliwindow.h"
#include "border.h"
#include <map>
#include <string>
#include <sstream>
#include <exception> 

class UnknownLayoutException : public std::exception
{
private:
	void fillWhat();

public:
	std::string viewName;
	std::string layoutName;
	std::stringstream whatStr;

	UnknownLayoutException(const std::string&  viewName, const std::string& layoutName) throw();
	UnknownLayoutException(const UnknownLayoutException & e) throw();
	virtual ~UnknownLayoutException()throw(){}
	const char* what() const throw();
};


class NameDuplicateException : public std::exception
{
private:
	void fillWhat();

public:
	std::string viewName;
	std::string objectName;
	LayoutObject::ObjectType type;
	std::stringstream whatStr;

	NameDuplicateException(const std::string& viewName,
	                       const std::string& layoutName,
	                       LayoutObject::ObjectType type = LayoutObject::WINDOW
	                       ) throw();
	NameDuplicateException(const NameDuplicateException & e) throw();
	virtual ~NameDuplicateException()throw(){}
	const char* what() const throw();
};


class ParentIsWindowException : public std::exception
{
private:
	void fillWhat();

public:
	std::string viewName;
	std::string windowName;
	std::string layoutObjectName;
	std::stringstream whatStr;

	ParentIsWindowException(const std::string& viewName, 
	                        const std::string& windowName,
	                        const std::string& layoutObjectName)throw();
	ParentIsWindowException(const ParentIsWindowException & e) throw();
	virtual ~ParentIsWindowException()throw(){}
	const char* what() const throw();
};


class UnknownLayoutTypeException : public std::exception
{
private:
	void fillWhat();

public:
	std::string viewName;
	std::string layoutName;
	LayoutObject::ObjectType type;
	std::stringstream whatStr;

	UnknownLayoutTypeException(const std::string& viewName, 
	                           const std::string& layoutName,
	                           LayoutObject::ObjectType type)throw();
	UnknownLayoutTypeException(const UnknownLayoutTypeException & e) throw();
	virtual ~UnknownLayoutTypeException()throw(){}
	const char* what() const throw();
};


//----------------------------------------------------------------------------//


class View
{
private:
	std::string name;
	LayoutObject *rootObject;
	std::map<std::string, LayoutObject*> layoutMap;
	std::map<std::string, CLIWindow*> windowMap;
	BorderBuffer borderBuffer;

	LayoutObject * createObj(LayoutObject::ObjectType type, 
	                         const std::string& objectName);

public:
	View(const std::string & name);
	~View();

	void addLayout(LayoutObject::ObjectType type,
	               const std::string & layoutName, 
	               const std::string & parentName = "");
	CLIWindow * addWindow(const std::string & windowName, 
	                      const std::string & parentName = "");
	void removeObject(const std::string & name);

	LayoutObject *getRoot();
};