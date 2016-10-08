#pragma once
#include "layoutobject.h"
#include "layout.h"


class VLayout : public LayoutObject, public Layout
{
public:
	VLayout(const SizeHint & sizeHint = DEFAULT_SIZE_HINT,
		    bool drawBorder = true);
	virtual ~VLayout();

	//implementation virtual methods from LayoutObject
	void setSize(unsigned int width, unsigned int height, const Border & border = Border());
	void toStream(std::ostream & os, unsigned int lineIndex) const;
	void borderToBuffer(BorderBuffer& buffer, unsigned int lineOffset, unsigned int columnOffset);
	
private:
	//implementation virtual methods from LayoutObject
	SizeHint calcSizeHint();
};
