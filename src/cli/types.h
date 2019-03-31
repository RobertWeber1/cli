#pragma once
#include <stdint.h>

namespace cli
{


template<class T>
struct Assignable
{
	T & operator=(T const& other)
	{
		static_cast<T&>(this).value = other.value;
	}
};


template<class T>
struct EqualComparable
{
	bool operator==(T const& other) const
	{
		return static_cast<T const&>(*this).value == other.value;
	}

	bool operator!=(T const& other) const
	{
		return static_cast<T const&>(*this).value != other.value;
	}
};



template<class REP, class TAG, template<class> class ... SKILLS>
struct Type : SKILLS<Type<REP, TAG, SKILLS ...>> ...
{
	REP value;

	explicit Type(REP val)
	: value(val)
	{}
};


template<class REP, class TAG>
using SkilledType = Type<REP, TAG, Assignable, EqualComparable>;


template<class REP, class TAG, class AFFINE_TO_TAG>
struct AffineType : SkilledType<REP, TAG>
{
	using affine_to_t = SkilledType<REP, AFFINE_TO_TAG>;

	using SkilledType_t = SkilledType<REP, TAG>;
	using SkilledType_t::SkilledType_t;
};


//----------------------------------------------------------------------------//


template<class REP, class TAG, class AFFINE_TAG>
auto operator+(AffineType<REP, TAG, AFFINE_TAG> lhs, SkilledType<REP, AFFINE_TAG> rhs)
{
	return AffineType<REP, TAG, AFFINE_TAG>(lhs.value + rhs.value);
}


template<class REP, class TAG, class AFFINE_TAG>
auto operator+(SkilledType<REP, AFFINE_TAG> lhs, AffineType<REP, TAG, AFFINE_TAG> rhs)
{
	return AffineType<REP, TAG, AFFINE_TAG>(lhs.value + rhs.value);
}


//----------------------------------------------------------------------------//


template<class REP, class TAG, class AFFINE_TAG>
auto operator-(AffineType<REP, TAG, AFFINE_TAG> lhs, SkilledType<REP, AFFINE_TAG> rhs)
{
	return AffineType<REP, TAG, AFFINE_TAG>(lhs.value - rhs.value);
}


//----------------------------------------------------------------------------//


template<class REP, class TAG, class AFFINE_TAG>
auto operator-(AffineType<REP, TAG, AFFINE_TAG> lhs, AffineType<REP, TAG, AFFINE_TAG> rhs)
{
	return SkilledType<REP, AFFINE_TAG>(lhs.value - rhs.value);
}


//----------------------------------------------------------------------------//


template<class REP, class TAG>
auto operator+(SkilledType<REP, TAG> lhs, SkilledType<REP, TAG> rhs)
{
	return SkilledType<REP, TAG>(lhs.value + rhs.value);
}


template<class REP, class TAG>
auto operator-(SkilledType<REP, TAG> lhs, SkilledType<REP, TAG> rhs)
{
	return SkilledType<REP, TAG>(lhs.value - rhs.value);
}


//----------------------------------------------------------------------------//


template<class REP, class TAG>
auto operator*(SkilledType<REP, TAG> lhs, int rhs)
{
	return SkilledType<REP, TAG>(lhs.value * rhs);
}


template<class REP, class TAG>
auto operator/(SkilledType<REP, TAG> lhs, int rhs)
{
	return SkilledType<REP, TAG>(lhs.value / rhs);
}


template<class REP, class TAG>
auto operator%(SkilledType<REP, TAG> lhs, int rhs)
{
	return SkilledType<REP, TAG>(lhs.value % rhs);
}


//----------------------------------------------------------------------------//


template<class REP>
using ColDistance = SkilledType<REP, struct CollumnTag>;

template<class REP>
using RowDistance = SkilledType<REP, struct RowTag>;


template<class REP>
using Collumn = AffineType<REP, struct ColDistTag, struct CollumnTag>;

template<class REP>
using Row = AffineType<REP, struct RowDistTag, struct RowTag>;



} //namespace cli
