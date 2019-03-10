#include "size_constraint.h"
#include <math.h>
#include <algorithm>

namespace CLI
{

namespace util
{

const unsigned int SizeConstraint::DEFAULT_MIN_SIZE = 3;
const unsigned int SizeConstraint::DEFAULT_MAX_SIZE = 1000;
const unsigned int SizeConstraint::DEFAULT_FACTOR = 1;


SizeConstraint::SizeConstraint(
	unsigned int min_val,
	unsigned int max_val,
	unsigned int factor )
: _min_val( min_val )
, _max_val( max_val )
, _factor( factor )
{}


void SizeConstraint::set(
	unsigned int new_min,
	unsigned int new_max,
	unsigned int new_faktor )
{
	_min_val = new_min;
	_max_val = new_max;
	_factor = new_faktor;
}

unsigned int SizeConstraint::min_val() const
{
	return _min_val;
}


void SizeConstraint::min_val( unsigned int new_value )
{
	_min_val = new_value;
}


unsigned int SizeConstraint::max_val() const
{
	return _max_val;
}


void SizeConstraint::max_val( unsigned int new_value )
{
	_max_val = new_value;
}


unsigned int SizeConstraint::factor() const
{
	return _factor;
}


void SizeConstraint::factor( unsigned int new_value )
{
	_factor = new_value;
}


void SizeConstraint::add( SizeConstraint const& operand )
{
	_min_val += operand.min_val();
	_max_val += operand.max_val();
	_factor += operand.factor();
}


void SizeConstraint::max( SizeConstraint const& operand )
{
	_min_val = std::max(_min_val, operand.min_val() );
	_max_val = std::max(_max_val, operand.max_val() );
	_factor = std::max(_factor, operand.factor() );
}


void SizeConstraint::clear()
{
	_min_val = 0;
	_max_val = 0;
	_factor = 0;
}


unsigned int SizeConstraint::match( unsigned int x ) const
{
	unsigned int result = x * _factor;
	if(result < _min_val)
	{
		result = _min_val;
	}
	if(result > _max_val)
	{
		result = _max_val;
	}
	return result;
}


unsigned int SizeConstraint::grow(
	unsigned int current,
	unsigned int remaining,
	unsigned int globalFactor ) const
{
	unsigned int newVal = current +
	                      ceil((float)remaining/(float)globalFactor) *
	                      _factor;

	if(newVal > _max_val)
	{
		newVal = _max_val;
	}
	//TODO: check if underflow can happen
	return newVal - current;
}


} //namespace util

} //CLI
