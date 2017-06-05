#pragma once

namespace CLI
{

namespace util
{

class SizeConstraint
{
public:
	static const unsigned int DEFAULT_MIN_SIZE;
	static const unsigned int DEFAULT_MAX_SIZE;
	static const unsigned int DEFAULT_FACTOR;


	SizeConstraint(
		unsigned int min_val = DEFAULT_MIN_SIZE,
		unsigned int max_val = DEFAULT_MAX_SIZE,
		unsigned int factor = DEFAULT_FACTOR );

	void set(
		unsigned int new_min,
		unsigned int new_max,
		unsigned int new_faktor );

	unsigned int min_val() const;

	void min_val( unsigned int new_value );

	unsigned int max_val() const;

	void max_val( unsigned int new_value );

	unsigned int factor() const;

	void factor( unsigned int new_value );

	void add( SizeConstraint const& operand );

	void max( SizeConstraint const& operand );

	void clear();

	unsigned int match( unsigned int x ) const;

	unsigned int grow(
		unsigned int current,
		unsigned int remaining,
		unsigned int globalFactor ) const;


private:
	unsigned int _min_val;
	unsigned int _max_val;
	unsigned int _factor;
};


} //namespace layout

} //namespace CLI
