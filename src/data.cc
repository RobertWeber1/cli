#include "data.h"
#include "util.h"
#include <iostream>
#include <cstdio>
#include <iterator>

Data & operator<<(Data & data, Data::CommandID cmdID)
{
	data << "\033" << (char)cmdID << ";";
 	return data;
}


std::ostream & operator<<(std::ostream & os, Data::CommandID cmdID)
{
	os << Data::commandNames[static_cast<int>(cmdID)];
	return os;
}


std::ostream & operator<<(std::ostream & os, Data::Position pos)
{
	os << Data::positionNames[static_cast<int>(pos)];
	return os;
}


const std::string Data::commandNames[] = {
	"NONE",
	"AUTO_UPDATE",
	"MANUAL_UPDATE",
	"UPDATE",
	"CLEAR_LINES",
	"ALIGNMENT",
	"ATTRIBUTE",
	"COLOR",
	"INSERT_POSITION",
	"EDIT_LINE",
	"REMOVE_LINE"
};

const std::string Data::positionNames[] = {
	"FRONT",
	"BACK",
	"LINE_NUMBER"
};


Data::Data() :
	autoUpdate(true),
	inSequence(false),
	currentCommand(CMD_NONE),
	currentLine(new Line("")),
	shadowLine(NULL),
	currentPosition(Data::BACK),
	editLine(false),
	editText(false),
	editLineIndex(0)
{}


Data::~Data()
{
	if(currentLine)
	{
		delete currentLine;
	}
	clearLines();
}


void Data::processData()
{
	int input;
	//std::cout << "in_avail: " << this->rdbuf()->in_avail() << std::endl;
	//std::cout << "str:      " << this->str() << std::endl;

	while((input = this->get()) != EOF)
	{
	//	std::cout << "input: " << (char)(input&0xff) << std::endl;
		if(inSequence)
		{
			if(input == ';')
			{
				inSequence = false;
				if(inArg)
				{
					args.push_back(currentArg);
				}

				processCommand(currentCommand, args);

				continue;
			}

			if(currentCommand == CMD_NONE)
			{

				//std::cout << "input: " << (char)(input&0xff) << std::endl;

				currentCommand = static_cast<CommandID>(input&0xff);
				continue;
			}

			if(input == ',')
			{
				args.push_back(currentArg);
				inArg = false;
				currentArg = 0;
				continue;
			}

			currentArg = (currentArg << 8) | (input & 0xff);
			inArg = true;
		}
		else
		{
			if(input == '\033')
			{
				inSequence = true;
				currentCommand = CMD_NONE;
				currentArg = 0;
				inArg = false;
				args.clear();
				continue;
			}

			if(input == '\n')
			{
				//std::cout << "text: " << currentLine->text << std::endl;
				if(editLine)
				{
					editLine = false;
					editText = false;
					currentLine = shadowLine;
					shadowLine = NULL;
				}
				else
				{
					switch(currentPosition)
					{
					case FRONT:
						lines.push_front(currentLine);
						break;
					case BACK:
						lines.push_back(currentLine);
						break;
					case LINE_NUMBER:
						if(insertLineNumber < lines.size())
						{
							std::list<Line*>::iterator it = lines.begin();
							std::advance(it, insertLineNumber);
							lines.insert(it, currentLine);
						}
						else
						{
							lines.push_back(currentLine);
						}
						break;
					}

					currentLine = new Line("");
				}

				if(autoUpdate)
				{
					update();
				}

				continue;
			}

			if(editLine)
			{
				if(!editText)
				{
					editText = true;
					currentLine->text = "";
				}
			}

			currentLine->text.append((char*)&input, 1);
		}
	}

	this->clear();
	this->str().clear();
}


void Data::processCommand(CommandID cmd, std::vector<int> & args)
{
	switch(cmd)
	{
		case CMD_AUTO_UPDATE:
			std::cout << "command: " << cmd << std::endl;
			autoUpdate = true;
			break;

		case CMD_MANUAL_UPDATE:
			std::cout << "command: " << cmd << std::endl;
			autoUpdate = false;
			break;

		case CMD_UPDATE:
			std::cout << "command: " << cmd << std::endl;
			update();
			break;

		case CMD_CLEAR_LINES:
			// std::cout << "command: " << cmd << std::endl;
			clearLines();
			if(autoUpdate)
			{
				update();
			}
			break;

		case CMD_ALIGNMENT:
			// std::cout << "command: " << cmd << " [" << static_cast<Line::Alignment>(args[0]) << "]" << std::endl;
			currentLine->alignment = static_cast<Line::Alignment>(args[0]);
			break;

		case CMD_ATTRIBUTE:
			// std::cout << "command: " << cmd << " [" << static_cast<Line::Attribute>(args[0]) << "]" << std::endl;
			currentLine->attribute = static_cast<Line::Attribute>(args[0]);
			break;

		case CMD_COLOR:
			// std::cout << "command: " << cmd << " [" << static_cast<Line::Color>(args[0])
			//           << ", " << static_cast<Line::Color>(args[1]) << "]" << std::endl;
			currentLine->forground = static_cast<Line::Color>(args[0]);
			currentLine->background = static_cast<Line::Color>(args[1]);
			break;

		case CMD_INSERT_POSITION:
			// std::cout << "command: " << cmd << " [" << static_cast<Position>(args[0]) << ", " << args[1] << "]" << std::endl;
			currentPosition = static_cast<Position>(args[0]);
			insertLineNumber = args[1];
			break;

		case CMD_EDIT_LINE:
			// std::cout << "command: " << cmd << std::endl;

			if(args[0] < lines.size())
			{
				if(!editLine)
				{
					shadowLine = currentLine;
				}
				std::list<Line*>::iterator it = lines.begin();
				std::advance(it, args[0]);
				currentLine = *it;
				editLine = true;
				editText = false;
			}
			break;

		case CMD_NONE:
		default:
		break;
	}
}


void Data::update()
{

}


void Data::clearLines()
{
	for(std::list<Line*>::iterator it = lines.begin(); it != lines.end(); it++)
	{
		delete (*it);
	}
	lines.clear();
}


const std::string Data::AUTO_UPDATE = "\033\001;";
const std::string Data::MANUAL_UPDATE = "\033\002;";
const std::string Data::UPDATE = "\033\003;";
const std::string Data::CLEAR_LINES = "\033\004;";


std::string Data::COLOR(Line::Color forground, Line::Color background, bool useAsDefault)
{
	std::string result("\033");

	CommandID c = Data::CMD_COLOR;
	result.append((char*)&c, 1);
	result.append((char*)&forground, 1);
	result.append(",", 1);
	result.append((char*)&background, 1);
	if(useAsDefault)
	{
		result.append(",D", 2);
	}
	result.append(";", 1);

	return result;
}


std::string Data::ALIGNMENT(Line::Alignment type, bool useAsDefault)
{
	std::string result("\033");
	CommandID a = Data::CMD_ALIGNMENT;

	result.append((char*)&a, 1);
	result.append((char*)&type, 1);
	if(useAsDefault)
	{
		result.append(",D", 2);
	}
	result.append(";", 1);

	return result;
}


std::string Data::INSERT_POS(Position pos, unsigned int lineNumber, bool useAsDefault)
{
	std::string result("\033");
	CommandID l = Data::CMD_INSERT_POSITION;

	result.append((char*)&l, 1);
	result.append((char*)&pos, 1);
	result.append(",", 1);
	for(int i=3; i>=0; i--)
	{
		char part = (char)((lineNumber >> 8*i)&0xff);
		result.append(&part, 1);
	}
	if(useAsDefault)
	{
		result.append(",D", 2);
	}
	result.append(";", 1);

	return result;
}


std::string Data::ATTRIBUTE(Line::Attribute attr, bool useAsDefault)
{
	std::string result("\033");
	CommandID a = Data::CMD_ATTRIBUTE;

	result.append((char*)&a, 1);
	result.append((char*)&attr, 1);
	if(useAsDefault)
	{
		result.append(",D", 2);
	}
	result.append(";", 1);

	return result;
}


std::string Data::EDIT_LINE(unsigned int lineNumber)
{
	std::string result("\033");
	CommandID e = Data::CMD_EDIT_LINE;

	result.append((char*)&e, 1);
	for(int i=3; i>=0; i--)
	{
		char part = (char)((lineNumber >> 8*i)&0xff);
		result.append(&part, 1);
	}
	result.append(";", 1);

	return result;
}


std::string Data::REMOVE_LINE(unsigned int lineNumber)
{
	std::string result("\033");
	CommandID r = Data::CMD_REMOVE_LINE;

	result.append((char*)&r, 1);
	for(int i=3; i>=0; i--)
	{
		char part = (char)((lineNumber >> 8*i)&0xff);
		result.append(&part, 1);
	}
	result.append(";", 1);

	return result;
}



void Data::dbgPrint(std::ostream & os)
{
	for(std::list<Line*>::iterator it = lines.begin(); it != lines.end(); it++)
	{
		os << (*it) << std::endl;
	}
}


std::pair<unsigned int, unsigned int> Data::unitTest(bool verbose)
{
	unsigned int successful = 0;
    unsigned int count = 0;
	Data dat1;


	dat1 << "test line 1" << std::endl;
	dat1 << "test line 2" << std::endl;
	dat1 << "test line 3" << std::endl;
	dat1.processData();
	std::stringstream result;
	dat1.dbgPrint(result);
	checkEq(result.str(),
"Text: test line 1, Fg: WHITE, Bg: BLACK, Attr: NONE, Alignm: LEFT\n\
Text: test line 2, Fg: WHITE, Bg: BLACK, Attr: NONE, Alignm: LEFT\n\
Text: test line 3, Fg: WHITE, Bg: BLACK, Attr: NONE, Alignm: LEFT\n", successful, count);


	dat1 << Data::CLEAR_LINES;
	dat1.processData();
	std::stringstream result2;
	dat1.dbgPrint(result2);
	checkEq(result2.str(), "", successful, count);


	dat1 << Data::COLOR(Line::RED, Line::GREEN) << "test line 1" << std::endl;
	dat1 << Data::ALIGNMENT(Line::RIGHT) << "test line 2" << std::endl;
	dat1 << Data::ATTRIBUTE(Line::BOLD) << "test line 3" << std::endl;
	dat1.processData();
	std::stringstream result3;
	dat1.dbgPrint(result3);
	checkEq(result3.str(),
"Text: test line 1, Fg: RED, Bg: GREEN, Attr: NONE, Alignm: LEFT\n\
Text: test line 2, Fg: WHITE, Bg: BLACK, Attr: NONE, Alignm: RIGHT\n\
Text: test line 3, Fg: WHITE, Bg: BLACK, Attr: BOLD, Alignm: LEFT\n", successful, count);


	dat1 << Data::CLEAR_LINES;
	dat1 << "test line 1" << std::endl;
	dat1 << "test line 2" << std::endl;
	dat1 << "test line 3" << std::endl;
	dat1 << Data::INSERT_POS(Data::FRONT) << "test line 0" << std::endl;
	dat1.processData();
	std::stringstream result4;
	dat1.dbgPrint(result4);
	checkEq(result4.str(),
"Text: test line 0, Fg: WHITE, Bg: BLACK, Attr: NONE, Alignm: LEFT\n\
Text: test line 1, Fg: WHITE, Bg: BLACK, Attr: NONE, Alignm: LEFT\n\
Text: test line 2, Fg: WHITE, Bg: BLACK, Attr: NONE, Alignm: LEFT\n\
Text: test line 3, Fg: WHITE, Bg: BLACK, Attr: NONE, Alignm: LEFT\n", successful, count);


	dat1 << Data::INSERT_POS(Data::BACK);
	dat1 << Data::CLEAR_LINES;
	dat1 << "test line 1" << std::endl;
	dat1 << "test line 2" << std::endl;
	dat1 << "test line 3" << std::endl;
	dat1 << Data::INSERT_POS(Data::LINE_NUMBER, 2) << "test line insert" << std::endl;
	dat1.processData();
	std::stringstream result5;
	dat1.dbgPrint(result5);
	checkEq(result5.str(),
"Text: test line 1, Fg: WHITE, Bg: BLACK, Attr: NONE, Alignm: LEFT\n\
Text: test line 2, Fg: WHITE, Bg: BLACK, Attr: NONE, Alignm: LEFT\n\
Text: test line insert, Fg: WHITE, Bg: BLACK, Attr: NONE, Alignm: LEFT\n\
Text: test line 3, Fg: WHITE, Bg: BLACK, Attr: NONE, Alignm: LEFT\n", successful, count);

	dat1 << Data::EDIT_LINE(1) << "edited Line!!!!" << Data::COLOR(Line::BLUE, Line::YELLOW) << Data::EDIT_LINE(0) << "second edit" << std::endl;
	dat1.processData();
	std::stringstream result6;
	dat1.dbgPrint(result6);
	checkEq(result6.str(),
"Text: second edit, Fg: WHITE, Bg: BLACK, Attr: NONE, Alignm: LEFT\n\
Text: edited Line!!!!, Fg: BLUE, Bg: YELLOW, Attr: NONE, Alignm: LEFT\n\
Text: test line insert, Fg: WHITE, Bg: BLACK, Attr: NONE, Alignm: LEFT\n\
Text: test line 3, Fg: WHITE, Bg: BLACK, Attr: NONE, Alignm: LEFT\n", successful, count);


	return std::pair<unsigned int, unsigned int>(successful, count);
}




