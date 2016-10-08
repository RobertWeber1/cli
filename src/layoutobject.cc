#include "layoutobject.h"
#include <algorithm>
#include <math.h>

const unsigned int LayoutObject::MIN_SIZE = 1;
const unsigned int LayoutObject::MAX_SIZE = 1000;
const unsigned int LayoutObject::DEFAULT_FACTOR = 1;
const LayoutObject::SizeHint LayoutObject::DEFAULT_SIZE_HINT(3,
                                                             LayoutObject::MAX_SIZE,
                                                             LayoutObject::DEFAULT_FACTOR,
                                                             3, 
                                                             LayoutObject::MAX_SIZE,
                                                             LayoutObject::DEFAULT_FACTOR);


LayoutObject::SizeConstraint::SizeConstraint(unsigned int minVal, 
                                             unsigned int maxVal,
                                              unsigned int factor):
	 minVal(minVal), maxVal(maxVal), factor(factor)
{}


void LayoutObject::SizeConstraint::add(const LayoutObject::SizeConstraint & operand)
{
	minVal += operand.minVal;
	maxVal += operand.maxVal;
	factor += operand.factor;
}


void LayoutObject::SizeConstraint::max(const LayoutObject::SizeConstraint & operand)
{
	minVal = std::max(minVal, operand.minVal);
	maxVal = std::max(maxVal, operand.maxVal);
	factor = std::max(factor, operand.factor);
}


void LayoutObject::SizeConstraint::toStream(std::ostream & os) const
{
 	os << "[" <<minVal << "," << maxVal << "]:" << factor << "x";
}


void LayoutObject::SizeConstraint::clear()
{
	minVal = 0;
	maxVal = 0;
	factor = 0;
}


unsigned int LayoutObject::SizeConstraint::calc(unsigned int x) const
{
	unsigned int result = x * factor;
	if(result < minVal)
	{
		result = minVal;
	}
	if(result > maxVal)
	{
		result = maxVal;
	}
	return result;
}


unsigned int LayoutObject::SizeConstraint::grow(unsigned int current,
                                                unsigned int remaining,
                                                unsigned int globalFactor)
{
	unsigned int newVal = current + ceil((float)remaining/(float)globalFactor) * factor;

	if(newVal > maxVal)
	{
		newVal = maxVal;
	}

	return newVal-current;
}


void LayoutObject::SizeConstraint::set(unsigned int newMinVal,
                                       unsigned int newMaxVal, 
                                       unsigned int newFaktor)
{
	minVal = newMinVal;
	maxVal = newMaxVal;
	factor = newFaktor;
}


std::ostream & operator<<(std::ostream& os, 
                          const LayoutObject::SizeConstraint& sizeConstraint)
{
	sizeConstraint.toStream(os);
	return os;
}


//----------------------------------------------------------------------------//


LayoutObject::SizeHint::SizeHint(SizeConstraint width, SizeConstraint height):
	 width(width), height(height)
{}

LayoutObject::SizeHint::SizeHint(unsigned int wMin,
                                 unsigned int wMax, 
                                 unsigned int wFactor,
                                 unsigned int hMin, 
                                 unsigned int hMax, 
                                 unsigned int hFactor)
{
	width.minVal = wMin;
	width.maxVal = wMax;
	width.factor = wFactor;
	height.minVal = hMin;
	height.maxVal = hMax;
	height.factor = hFactor;
}


void LayoutObject::SizeHint::clear()
{
	width.clear();
	height.clear();
}


std::ostream & operator<<(std::ostream& os, const LayoutObject::SizeHint& sizeHint)
{
	os << "W:" << sizeHint.width << ", H:" << sizeHint.height;
	return os;
}


//----------------------------------------------------------------------------//


unsigned int LayoutObject::getWidth()
{
	return width;
}


unsigned int LayoutObject::getHeight()
{
	return height;
}


const LayoutObject::SizeHint& LayoutObject::getSizeHint()
{
		calculatedSizeHint = calcSizeHint();
		return calculatedSizeHint;
}
