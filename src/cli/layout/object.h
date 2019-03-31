#pragma once
#include <cli/types.h>
#include <cli/layout/size_hint.h>

namespace cli
{

namespace layout
{


template<class WIDTH_HINT, class HEIGHT_HINT>
struct Object
{
	using WidthHint_t = WIDTH_HINT;
	using HeightHint_t = HEIGHT_HINT;

	X x = X(0);
	Y y = Y(0);
	Width width = get_min(WidthHint_t{});
	Height height = get_min(HeightHint_t{});
};


//----------------------------------------------------------------------------//


template<template<uint16_t, uint16_t, uint8_t> class, class>
struct get_hint;


template<class OBJ>
struct get_hint<WidthHint, OBJ>
{
	using type = typename OBJ::WidthHint_t;
};


template<class OBJ>
struct get_hint<HeightHint, OBJ>
{
	using type = typename OBJ::HeightHint_t;
};


//----------------------------------------------------------------------------//


template<class RET, RET ... ARGS>
constexpr RET accumulate()
{
	RET result = RET{};

	using dummy_ = int[];
	(void)dummy_{1, ((result += ARGS), void(), int{}) ... };

	return result;
}


template<template<uint16_t, uint16_t, uint8_t>class TYPE, class ... OBJECTS>
struct AddHints
{
	using type =
		TYPE<
			accumulate<uint16_t, get_raw<typename get_hint<TYPE, OBJECTS>::type >::min...>(),
			accumulate<uint16_t, get_raw<typename get_hint<TYPE, OBJECTS>::type >::max...>(),
			accumulate<uint8_t, get_raw<typename get_hint<TYPE, OBJECTS>::type >::factor...>()>;
};


//----------------------------------------------------------------------------//


template<class RET, RET ... ARGS>
constexpr RET maximum()
{
	RET result = RET{};

	using dummy_ = int[];
	(void)dummy_{1, ((result = ((ARGS>result) ? ARGS : result)), void(), int{}) ... };

	return result;
}


template<template<uint16_t, uint16_t, uint8_t>class TYPE, class ... OBJECTS>
struct MaxHints
{
	using type =
		TYPE<
			maximum<uint16_t, get_raw<typename get_hint<TYPE, OBJECTS>::type >::min...>(),
			maximum<uint16_t, get_raw<typename get_hint<TYPE, OBJECTS>::type >::max...>(),
			maximum<uint8_t, get_raw<typename get_hint<TYPE, OBJECTS>::type >::factor...>()>;
};


} //namespace layout

} //namespace cli
