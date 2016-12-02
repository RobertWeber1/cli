#pragma once
#include <sstream>
#include <vector>
#include "line.h"

class Data : public std::stringstream
{
private:
	typedef enum CommandID{
		ENABLE_AUTO_UPDATE = 0,
		DISABLE_AUTO_UPDATE,
		BOLD,
		ITALIC,
		INVERS,
		RED,
		GREEN,
		BULUE,
		YELLOW,
		CYAN,
		MAGENTHA,
		CLEAR_WINDOW,
		CLEAR_SCREEN
	}Command;

	std::vector<Line> lines;
	bool autoUpdate;
	static const std::map<std::string, int> commandMap;

	static const std::string commandNames[];

	static std::map<std::String> initCommandMap;

public:
	Data();
	virtual ~Data();

	void processData();
	void dbgToStream(std::ostream &);
};

std::stringstream & operator(std::stringstream & os, Data::CommandID cmdID);