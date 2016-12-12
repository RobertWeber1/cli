#include "data.h"
#include <iostream>
#include <cstdio>


const std::string Data::commandNames[] = {
	"NONE",
	"AUTO_UPDATE",
	"MANUAL_UPDATE",
	"UPDATE",
	"BOLD",
	"ITALIC",
	"INVERS",
	"ALIGNMENT",
	"COLOR",
	"CLEAR_WINDOW",
	"POSITION"
};

const std::string Data::positionNames[] = {
	"FRONT",
	"BACK",
	"LINE_NUMBER"
};



Data::Data() :
	autoUpdate(true),
	inSequence(false),
	currentCommand(NONE)
{}


Data::~Data()
{
	this->clear();
	this->str().clear();
}


void Data::processData()
{
	int input;
	//std::cout << "in_avail: " << this->rdbuf()->in_avail() << std::endl;
	//std::cout << "str:      " << this->str() << std::endl;



	while((input = this->get()) != EOF)
	{
		//std::cout << "input: " << (char)(input&0xff) << std::endl;

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

			if(currentCommand == NONE)
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
				currentCommand = NONE;
				currentArg = 0;
				inArg = false;
				args.clear();
				continue;
			}

			if(input == '\n')
			{
				std::cout << "text: " << text << std::endl;
				text.clear();
				continue;
			}

			text.append((char*)&input, 1);
		}
	}

	this->clear();
	this->str().clear();
	//this->str() = "";
}


void Data::processCommand(CommandID cmd, std::vector<int> & args)
{
	switch(cmd)
	{
		case AUTO_UPDATE:
			std::cout << "command: " << cmd << std::endl;
			autoUpdate = true;
			break;
		case MANUAL_UPDATE:
			std::cout << "command: " << cmd << std::endl;
			autoUpdate = false;
			break;
		case UPDATE:
			std::cout << "command: " << cmd << std::endl;
			break;
		case COLOR:
//			std::cout << "command: " << cmd << " [" << static_cast<Line::Color>(args[0])
//			          << ", " << static_cast<Line::Color>(args[1]) << "]" << std::endl;
			break;
		case ALIGNMENT:
//			std::cout << "command: " << cmd << " [" << static_cast<Line::Alignment>(args[0]) << "]" << std::endl;
			break;
		case BOLD:
			std::cout << "command: " << cmd << std::endl;
			break;
		case ITALIC:
			std::cout << "command: " << cmd << std::endl;
			break;
		case INVERS:
			std::cout << "command: " << cmd << std::endl;
			break;
		case CLEAR_WINDOW:
			std::cout << "command: " << cmd << std::endl;
			break;
		case LINE:
			std::cout << "command: " << cmd << " [" << static_cast<Position>(args[0]) << ", " << args[1] << "]" << std::endl;
			break;
		default:
		break;
	}
}


std::string Data::SET_COLOR(Line::Color forground, Line::Color background)
{
	std::string result("\033");

	CommandID c = Data::COLOR;
	result.append((char*)&c, 1);
	result.append((char*)&forground, 1);
	result.append(",", 1);
	result.append((char*)&background, 1);
	result.append(";", 1);

	return result;
}

std::string Data::SET_ALIGNMENT(Line::Alignment type)
{
	std::string result("\033");
	CommandID a = Data::ALIGNMENT;

	result.append((char*)&a, 1);
	result.append((char*)&type, 1);
	result.append(";", 1);

	return result;
}


std::string Data::SET_LINE(Position pos, unsigned int lineNumber)
{
	std::string result("\033");
	CommandID l = Data::LINE;

	result.append((char*)&l, 1);
	result.append((char*)&pos, 1);
	result.append(",", 1);
	for(int i=3; i>=0; i--)
	{
		char part = (char)((lineNumber >> 8*i)&0xff);
		result.append(&part, 1);
	}
	result.append(";", 1);

	return result;
}

void Data::dbgToStream(std::ostream & os)
{

}


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

