#pragma once

#include <streambuf>
#include <string>
#include <map>
#include <vector>
#include <iostream>

class LockupMap 
{
public:
	typedef enum ControlCharacter
	{
		NUL = 0, 
		SOH = 1, 
		STX = 2, 
		ETX = 3, 
		EOT = 4, 
		ENQ = 5, 
		ACK = 6, 
		BEL = 7, 
		BS  = 8, 
		TAB = 9, 
		LF  = 10, 
		VT  = 11, 
		FF  = 12, 
		CR  = 13, 
		SO  = 14, 
		SI  = 15, 
		DLE = 16, 
		DC1 = 17, 
		DC2 = 18, 
		DC3 = 19, 
		DC4 = 20, 
		NAK = 21, 
		SYN = 22, 
		ETB = 23, 
		CAN = 24, 
		EM  = 25, 
		SUB = 26, 
		ESC = 27, 
		FS  = 28, 
		GS  = 29, 
		RS  = 30, 
		US  = 31, 
		DEL = 127
	}ControlCharacter;

	typedef enum ControlSequenceID
	{
		FOO
	}ControlSequenceID;

	typedef enum MultiByteKeyID
	{
		F1         = 0x3b,
		F2         = 0x3c,
		F3         = 0x3d,
		F4         = 0x3e,
		F5         = 0x3f,
		F6         = 0x40,
		F7         = 0x41,
		F8         = 0x42,
		F9         = 0x43,
		F10        = 0x44,
		HOME       = 0x47,
		UP         = 0x48,
		PAGE_UP    = 0x49,
		LEFT       = 0x51,
		RIGHT      = 0x53,
		END        = 0x55,
		DOWN       = 0x56,
		PAGE_DOWN  = 0x57,
		INSERT     = 0x58,
		DELETE     = 0x59,
		PRINT      = 0x72,
		F11        = 0x85,
		F12        = 0x86
	}MultiByteKeyID;
private:
	static const std::string emptyString;
	static const std::map<char, std::string> controlCharMap;
	static std::map<char, std::string> initMap();

public:
	LockupMap();
	const std::string & lookup(char input);
};


class InputMultiplexer : public std::streambuf
{
public:
	

private:	
	LockupMap cclMap;
	std::streambuf *oldBuf;
	std::istream & inStream;
public:
	InputMultiplexer(std::istream& inStream = std::cin);
	~InputMultiplexer();

	void processChar(char c);

	virtual void visibleCharEntered(char c);
	virtual void controlCharEntered(char c);
	virtual void controlSequenceEntered(LockupMap::ControlSequenceID controlSequenceID, const std::vector<std::string>& args);


	//implementation of std::streambuf virtual output functions
	std::streamsize xsputn(const char* s, std::streamsize n);
	int overflow(int in);

	//implementation of std::streambuf virtual output functions
	std::streamsize showmanyc();
	std::streamsize xsgetn(char* s, std::streamsize n);
	int underflow();
	int uflow();
	int pbackfail(int c);

};
