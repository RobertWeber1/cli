#pragma once
#include <cli/types.h>
#include <cstdint>

namespace cli
{

namespace layout
{


template<class TYPE, uint16_t MIN, uint16_t MAX, uint8_t FACTOR>
struct SizeHint
{
	static_assert(MIN<=MAX, "MIN must be less/equal to MAX");
};


//----------------------------------------------------------------------------//


template<class TYPE, uint16_t MIN, uint16_t MAX, uint8_t FACTOR>
TYPE get_min(SizeHint<TYPE, MIN, MAX, FACTOR>)
{
	return TYPE{MIN};
};


template<class TYPE, uint16_t MIN, uint16_t MAX, uint8_t FACTOR>
TYPE get_max(SizeHint<TYPE, MIN, MAX, FACTOR>)
{
	return TYPE{MAX};
};


template<class TYPE, uint16_t MIN, uint16_t MAX, uint8_t FACTOR>
uint8_t get_factor(SizeHint<TYPE, MIN, MAX, FACTOR>)
{
	return FACTOR;
};


//----------------------------------------------------------------------------//


template<class>
struct get_raw;


template<class TYPE, uint16_t MIN, uint16_t MAX, uint8_t FACTOR>
struct get_raw< SizeHint<TYPE, MIN, MAX, FACTOR> >
{
	static constexpr uint16_t min = MIN;
	static constexpr uint16_t max = MAX;
	static constexpr uint8_t factor = FACTOR;
};


template<class TYPE, uint16_t MIN, uint16_t MAX, uint8_t FACTOR>
constexpr uint16_t get_raw< SizeHint<TYPE, MIN, MAX, FACTOR> >::min;

template<class TYPE, uint16_t MIN, uint16_t MAX, uint8_t FACTOR>
constexpr uint16_t get_raw< SizeHint<TYPE, MIN, MAX, FACTOR> >::max;

template<class TYPE, uint16_t MIN, uint16_t MAX, uint8_t FACTOR>
constexpr uint8_t get_raw< SizeHint<TYPE, MIN, MAX, FACTOR> >::factor;


//----------------------------------------------------------------------------//


// template<class, class>
// struct Add;


// template<
// 	class TYPE,
// 	uint16_t MIN_L, uint16_t MAX_L, uint8_t FACTOR_L,
// 	uint16_t MIN_R, uint16_t MAX_R, uint8_t FACTOR_R>
// struct Add<
// 	SizeHint<TYPE, MIN_L, MAX_L, FACTOR_L>,
// 	SizeHint<TYPE, MIN_R, MAX_R, FACTOR_R>>
// {
// 	using type = SizeHint<TYPE, MIN_L+MIN_R, MAX_L+MAX_R, FACTOR_L+FACTOR_R>;
// };


// //----------------------------------------------------------------------------//

// template<class, class>
// struct Max;


// template<
// 	class TYPE,
// 	uint16_t MIN_L, uint16_t MAX_L, uint8_t FACTOR_L,
// 	uint16_t MIN_R, uint16_t MAX_R, uint8_t FACTOR_R>
// struct Max<
// 	SizeHint<TYPE, MIN_L, MAX_L, FACTOR_L>,
// 	SizeHint<TYPE, MIN_R, MAX_R, FACTOR_R>>
// {
// 	using type =
// 		SizeHint<
// 			TYPE,
// 			std::max(MIN_L,MIN_R),
// 			std::max(MAX_L,MAX_R),
// 			std::max(FACTOR_L,FACTOR_R)>;
// };


//----------------------------------------------------------------------------//

template<uint16_t MIN, uint16_t MAX, uint8_t FACTOR=1>
using WidthHint = SizeHint<Width, MIN, MAX, FACTOR>;

template<uint16_t MIN, uint16_t MAX, uint8_t FACTOR=1>
using HeightHint = SizeHint<Height, MIN, MAX, FACTOR>;


} //namespace layout

} //namespace cli
