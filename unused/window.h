#pragma once
#include "layoutobject.h"
#include "data.h"
#include "terminal.h"

namespace CLI
{

class Window : public LayoutObject
{
public:


private:
	unsigned int visibleCollumns, visibleLines;
	unsigned int lineOffset, collumnOffset;
	unsigned int firstLineIndex;
	bool borderInverted;
	Data * data;

public:

	Window(Data * data = NULL,
	       const SizeHint & sizeHint = LayoutObject::DEFAULT_SIZE_HINT);
	virtual ~Window();

	void setData(Data * data);


	SizeHint calcSizeHint();
	const SizeHint& getSizeHint();
 	void setSize(unsigned int collumnOffset,
	             unsigned int lineOffset,
	             unsigned int width,
	             unsigned int height);

	void toStream(std::ostream& os) const {};
//	void borderToBuffer(BorderBuffer& buffer) {};

	void renderContent(ITerminal * terminal);
	void renderBorder(ITerminal * terminal);

	static std::pair<unsigned int, unsigned int> unitTest(bool verbose=true);
};

}
