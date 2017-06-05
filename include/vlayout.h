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
	void setSize(unsigned int columnOffset,
                 unsigned int lineOffset,
                 unsigned int width,
                 unsigned int height);
	void toStream(std::ostream & os) const;
	void borderToBuffer(BorderBuffer& buffer);

private:
	//implementation virtual methods from LayoutObject
	SizeHint calcSizeHint();
};
