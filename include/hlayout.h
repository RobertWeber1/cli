#pragma once
#include "layoutobject.h"
#include "layout.h"


class HLayout : public LayoutObject, public Layout
{
public:
	HLayout(const SizeHint & sizeHint = DEFAULT_SIZE_HINT,
	        bool drawBorders = true);
	virtual ~HLayout();

	//implementation of virtual methods from LayoutObject
	void setSize(unsigned int width, unsigned int height, const Border & border = Border());
	void toStream(std::ostream & os, unsigned int lineIndex) const;
	void borderToBuffer(BorderBuffer& buffer, unsigned int lineOffset, unsigned int columnOffset);
	
private:
	//implementation virtual methods from LayoutObject
	SizeHint calcSizeHint();
};
