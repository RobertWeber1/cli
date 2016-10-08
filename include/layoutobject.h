#pragma once
#include "border.h"
#include <iostream>


class LayoutObject
{
public:
	static const unsigned int MIN_SIZE;
	static const unsigned int MAX_SIZE;
	static const unsigned int DEFAULT_FACTOR;


	typedef struct SizeConstraint
	{
		unsigned int minVal;
		unsigned int maxVal;
		unsigned int factor;

		SizeConstraint(unsigned int minVal = MIN_SIZE,
		               unsigned int maxVal = MAX_SIZE,
		               unsigned int factor = DEFAULT_FACTOR);

		void add(const LayoutObject::SizeConstraint & operand);

		void max(const LayoutObject::SizeConstraint & operand);

		void toStream(std::ostream & os) const;

		void clear();

		unsigned int calc(unsigned int x) const;

		unsigned int grow(unsigned int current, 
		                  unsigned int remaining, 
		                  unsigned int globalFactor);

		void set(unsigned int newMinVal, 
		         unsigned int newMaxVal, 
		         unsigned int newFaktor);
	}SizeConstraint;

	typedef struct SizeHint
	{
		SizeConstraint width;
		SizeConstraint height;
		SizeHint(SizeConstraint width = SizeConstraint(),
		         SizeConstraint height = SizeConstraint());
		SizeHint(unsigned int wMin, unsigned int wMax, unsigned int wFactor,
		         unsigned int hMin, unsigned int hMax, unsigned int hFactor);
		void clear();
	}SizeHint;

	static const SizeHint DEFAULT_SIZE_HINT;


protected:
	unsigned int width;
	unsigned int height;
	bool drawBorders;
	SizeHint defaultSizeHint;
	SizeHint calculatedSizeHint;
	

	virtual SizeHint calcSizeHint() = 0;
public:

	unsigned int getWidth();
	unsigned int getHeight();
	//virtual SizeHint& getSizeHint();

	LayoutObject(bool drawBorders, const SizeHint & sizeHint) :
		drawBorders(drawBorders), defaultSizeHint(sizeHint), width(3), height(3) {}

	virtual ~LayoutObject() {}

	virtual const SizeHint& getSizeHint();
	virtual void setSize(unsigned int width, unsigned int height, const Border & border = Border()) = 0;
	virtual void toStream(std::ostream& os, unsigned int lineIndex) const = 0;
	virtual void borderToBuffer(BorderBuffer& buffer, unsigned int lineOffset, unsigned int columnOffset) = 0;
};


std::ostream & operator<<(std::ostream& os, const LayoutObject::SizeConstraint& sizeConstraint);
std::ostream & operator<<(std::ostream& os, const LayoutObject::SizeHint& sizeHint);