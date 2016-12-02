#include "inputmultiplexer.h"
#include <iostream>
#include <iomanip>

const std::string LockupMap::emptyString = "";
const std::map<char, std::string> LockupMap::controlCharMap = LockupMap::initMap();


std::map<char, std::string> LockupMap::initMap()
{
	std::map<char, std::string> result;
	result[NUL] = "<NUL>";
	result[SOH] = "<SOH>";
	result[STX] = "<STX>";
	result[ETX] = "<ETX>";
	result[EOT] = "<EOT>";
	result[ENQ] = "<ENQ>";
	result[ACK] = "<ACK>";
	result[BEL] = "<BEL>";
	result[BS ] = "<BS>";
	result[TAB] = "<TAB>";
	result[LF ] = "<LF>";
	result[VT ] = "<VT>";
	result[FF ] = "<FF>";
	result[CR ] = "<CR>";
	result[SO ] = "<SO>";
	result[SI ] = "<SI>";
	result[DLE] = "<DLE>";
	result[DC1] = "<DC1>";
	result[DC2] = "<DC2>";
	result[DC3] = "<DC3>";
	result[DC4] = "<DC4>";
	result[NAK] = "<NAK>";
	result[SYN] = "<SYN>";
	result[ETB] = "<ETB>";
	result[CAN] = "<CAN>";
	result[EM ] = "<EM>";
	result[SUB] = "<SUB>";
	result[ESC] = "<ESC>";
	result[FS ] = "<FS>";
	result[GS ] = "<GS>";
	result[RS ] = "<RS>";
	result[US ] = "<US>";
	result[' '] = " ";
	result['!'] = "!";
	result['"'] = "\"";
	result['#'] = "#";
	result['$'] = "$";
	result['%'] = "%";
	result['&'] = "&";
	result['\''] = "\'";
	result['('] = "(";
	result[')'] = ")";
	result['*'] = "*";
	result['+'] = "+";
	result[','] = ",";
	result['-'] = "-";
	result['.'] = ".";
	result['/'] = "/";
	result['0'] = "0";
	result['1'] = "1";
	result['2'] = "2";
	result['3'] = "3";
	result['4'] = "4";
	result['5'] = "5";
	result['6'] = "6";
	result['7'] = "7";
	result['8'] = "8";
	result['9'] = "9";
	result[':'] = ":";
	result[';'] = ";";
	result['<'] = "<";
	result['='] = "=";
	result['>'] = ">";
	result['?'] = "?";
	result['@'] = "@";
	result['A'] = "A";
	result['B'] = "B";
	result['C'] = "C";
	result['D'] = "D";
	result['E'] = "E";
	result['F'] = "F";
	result['G'] = "G";
	result['H'] = "H";
	result['I'] = "I";
	result['J'] = "J";
	result['K'] = "K";
	result['L'] = "L";
	result['M'] = "M";
	result['N'] = "N";
	result['O'] = "O";
	result['P'] = "P";
	result['Q'] = "Q";
	result['R'] = "R";
	result['S'] = "S";
	result['T'] = "T";
	result['U'] = "U";
	result['V'] = "V";
	result['W'] = "W";
	result['X'] = "X";
	result['Y'] = "Y";
	result['Z'] = "Z";
	result['['] = "[";
	result['\\'] = "\\";
	result[']'] = "]";
	result['^'] = "^";
	result['_'] = "_";
	result['`'] = "`";
	result['a'] = "a";
	result['b'] = "b";
	result['c'] = "c";
	result['d'] = "d";
	result['e'] = "e";
	result['f'] = "f";
	result['g'] = "g";
	result['h'] = "h";
	result['i'] = "i";
	result['j'] = "j";
	result['k'] = "k";
	result['l'] = "l";
	result['m'] = "m";
	result['n'] = "n";
	result['o'] = "o";
	result['p'] = "p";
	result['q'] = "q";
	result['r'] = "r";
	result['s'] = "s";
	result['t'] = "t";
	result['u'] = "u";
	result['v'] = "v";
	result['w'] = "w";
	result['x'] = "x";
	result['y'] = "y";
	result['z'] = "z";
	result['{'] = "{";
	result['|'] = "|";
	result['}'] = "}";
	result['~'] = "~";
	result[DEL] = "<DEL>";
	
	return result;
}


const std::string & LockupMap::lookup(char input)
{
	if(input < 128)
	{
		std::map<char, std::string>::const_iterator findResult;
		findResult = controlCharMap.find(input);
		if(findResult != controlCharMap.end())
		{
			return findResult->second;
		}
		else
		{
			return emptyString;
		}
	}
	else
	{
		return emptyString;
	}
}


LockupMap::LockupMap()
{}





InputMultiplexer::InputMultiplexer(std::istream& inStream) : 
	inStream(inStream),
	oldBuf(inStream.rdbuf())
{
	std::cout << "start intercepting cin" << std::endl;
	inStream.rdbuf(this);
}


InputMultiplexer::~InputMultiplexer()
{
	std::cout << "stop intercepting cin" << std::endl;
	inStream.rdbuf(oldBuf);
}


void InputMultiplexer::processChar(char c)
{
	std::cout << std::setw(2) << std::setfill('0') << std::hex << (int)c << " ";
}


void InputMultiplexer::visibleCharEntered(char c)
{

}


void InputMultiplexer::controlCharEntered(char c)
{

}


void InputMultiplexer::controlSequenceEntered(LockupMap::ControlSequenceID controlSequenceID, const std::vector<std::string>& args)
{

}


//implementation of std::streambuf virtual output functions
std::streamsize InputMultiplexer::xsputn(const char* s, std::streamsize n)
{
	std::cout << "xsputn: ";
	for(int i=0; i<n; i++)
	{
		processChar(s[i]);
	}
	std::cout << std::endl;
}


int InputMultiplexer::overflow(int in)
{
	std::cout << "overflow: ";
	processChar(in);
	std::cout << std::endl;
}


std::streamsize InputMultiplexer::showmanyc()
{
	std::cout << "showmanyc: " << std::endl;
}
std::streamsize InputMultiplexer::xsgetn(char* s, std::streamsize n)
{
	std::cout << "showmanyc: " << std::endl;
}
int InputMultiplexer::underflow()
{
	std::cout << "underflow: " << std::endl;
}
int InputMultiplexer::uflow(){
	std::cout << "uflow: " << std::endl;
}

int InputMultiplexer::pbackfail(int c)
{
	std::cout << "pbackfail: " << std::endl;
}