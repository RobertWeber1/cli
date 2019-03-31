#pragma once
#include <cli/layout/object.h>
#include <cli/layout/size_hint.h>
#include <cli/types.h>
#include <tuple>

namespace cli
{

namespace layout
{


template<class ... ELEMENTS, size_t ... Is>
void set_size_(std::tuple<ELEMENTS...> const& tup, std::index_sequence<Is...>)
{

}


template<class ... ELEMENTS>
struct Horizontal
{
	using WidthHint_t = typename AddHints<WidthHint, ELEMENTS...>::type;
	using HeightHint_t = typename MaxHints<HeightHint, ELEMENTS...>::type;

	std::tuple<ELEMENTS...> children;

	void set_size(Width width, Height height)
	{}
};


} //namespace layout

} //namespace cli