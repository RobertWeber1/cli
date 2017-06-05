#pragma once
#include "size_constraint.h"

namespace CLI
{

namespace util
{

class SizeHint
{
public:
	SizeHint(SizeConstraint width = SizeConstraint(),
	         SizeConstraint height = SizeConstraint());
	// SizeHint(unsigned int wMin, unsigned int wMax, unsigned int wFactor,
	//          unsigned int hMin, unsigned int hMax, unsigned int hFactor);
	void clear();

	SizeConstraint const& width() const;

	SizeConstraint & width();

	void width( SizeConstraint const& new_width );

	SizeConstraint const& height() const;

	SizeConstraint & height();

	void height( SizeConstraint const& new_height );

private:
	SizeConstraint _width;
	SizeConstraint _height;
};

} //namespace util

} //namespace CLI
