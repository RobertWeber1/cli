#pragma once
#include <cli/char_sequence.h>
#include <utility>

namespace cli
{


inline
void get_size(size_t & result, int i)
{
	//TODO: estimate count of decimal digits
	if(i<=9)
	{
		result += 1;
	}
	else if(i<=99)
	{
		result += 2;
	}
	else if(i<=999)
	{
		result += 3;
	}
	else
	{
		result += 4;
	}
}


inline
void get_size(size_t & result, std::string const& s)
{
	result += 2 + s.size();
}


template<class ... ARGS, size_t ... Is>
void size_helper(size_t & result, std::tuple<ARGS...> const& tup, std::index_sequence<Is...>)
{
	result += sizeof...(ARGS) - 1;

	using dummy_ = int[];
	(void)dummy_{1, (get_size(result, std::get<Is>(tup)), void(), int{})... };
}


template<char CMD, class SEQ, class ... ARGS>
struct ParameterSequence
{
	std::tuple<ARGS...>  args_;

	ParameterSequence(ARGS ... args)
	: args_({args...})
	{}

	size_t size() const
	{
		size_t ret = sizeof(CMD) + SEQ::size();

		size_helper(ret, args_, std::make_index_sequence<sizeof...(ARGS)>{});

		return ret;
	}
};


} //namespace cli
