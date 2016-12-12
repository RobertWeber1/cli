#pragma once
#include <sstream>
#include <vector>
#include "line.h"

class Data : public std::stringstream
{
public:
	typedef enum CommandID{
		NONE = 0,
		AUTO_UPDATE,
		MANUAL_UPDATE,
		UPDATE,
		BOLD,
		ITALIC,
		INVERS,
		ALIGNMENT,
		COLOR,
		CLEAR_WINDOW,
		LINE,
		NORMAL
	}CommandID;

	typedef enum Position{
		FRONT = 0,
		BACK,
		LINE_NUMBER
	}Position;

	static const std::string commandNames[];
	static const std::string colorNames[];
	static const std::string alignmentNames[];
	static const std::string positionNames[];

private:
	std::string text;
	std::vector<Line> lines;
	bool autoUpdate;
	bool inSequence;
	CommandID currentCommand;
	std::vector<int> args;
	int currentArg;
	bool inArg;

	void processCommand(CommandID cmd, std::vector<int> & args);
public:
	Data();
	virtual ~Data();

	void processData();
	void dbgToStream(std::ostream &);

	static std::string SET_COLOR(Line::Color forground = Line::WHITE, Line::Color background = Line::BLACK);
	static std::string SET_ALIGNMENT(Line::Alignment type = Line::LEFT);
	static std::string SET_LINE(Position pos = BACK, unsigned int lineNumber = 0);

};

Data & operator<<(Data & data, Data::CommandID cmdID);
std::ostream & operator<<(std::ostream & os, Data::CommandID cmdID);
std::ostream & operator<<(std::ostream & os, Data::Position pos);