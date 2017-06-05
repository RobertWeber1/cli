#pragma once
#include <sstream>
#include <vector>
#include <list>
#include "line.h"

namespace CLI
{

class Data : public std::stringstream
{
public:
	typedef enum CommandID{
		CMD_NONE = 0,
		CMD_AUTO_UPDATE,
		CMD_MANUAL_UPDATE,
		CMD_UPDATE,
		CMD_CLEAR_LINES,
		CMD_ALIGNMENT,
		CMD_ATTRIBUTE,
		CMD_COLOR,
		CMD_INSERT_POSITION,
		CMD_EDIT_LINE,
		CMD_REMOVE_LINE
	}CommandID;

	typedef enum Position{
		FRONT = 0,
		BACK,
		LINE_NUMBER
	}Position;

	static const std::string commandNames[];
	static const std::string positionNames[];

private:
	Line::Color defaultFG, defaultBG;
	Line::Attribute defaultAttr;
	Line::Alignment defaultAlign;
	Line * currentLine;
	Line * shadowLine;
	Position currentPosition;
	unsigned int insertLineNumber;

	//std::string text;
	std::list<Line*> lines;
	bool autoUpdate;
	bool inSequence;
	CommandID currentCommand;
	std::vector<int> args;
	int currentArg;
	bool inArg;
	bool editLine;
	bool editText;
	unsigned int editLineIndex;

	void processCommand(CommandID cmd, std::vector<int> & args);
	void update();
	void clearLines();

public:
	Data();
	virtual ~Data();

	void processData();
	void dbgPrint(std::ostream &);

	std::list<Line*>::const_iterator getFirstLinesIter(unsigned int lineNumber) const;
	std::list<Line*>::const_iterator getEndLineIter() const;

	static const std::string AUTO_UPDATE;
	static const std::string MANUAL_UPDATE;
	static const std::string UPDATE;
	static const std::string CLEAR_LINES;
	static std::string ALIGNMENT(Line::Alignment type = Line::LEFT, bool useAsDefault = false);
	static std::string ATTRIBUTE(Line::Attribute attr = Line::NONE, bool useAsDefault = false);
	static std::string COLOR(Line::Color forground = Line::WHITE, Line::Color background = Line::BLACK, bool useAsDefault = false);
	static std::string INSERT_POS(Position pos = BACK, unsigned int lineNumber = 0, bool useAsDefault = false);
	static std::string EDIT_LINE(unsigned int lineNumber);
	static std::string REMOVE_LINE(unsigned int lineNumber);

	static std::pair<unsigned int, unsigned int> unitTest(bool verbose=true);
};

Data & operator<<(Data & data, Data::CommandID cmdID);
std::ostream & operator<<(std::ostream & os, Data::CommandID cmdID);
std::ostream & operator<<(std::ostream & os, Data::Position pos);

}
