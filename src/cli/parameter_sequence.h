#pragma once
#include <cli/char_sequence.h>
#include <cli/delimiter.h>
#include <utility>

namespace cli
{


template<char CMD, class SEQ, class ... ARGS>
struct ParameterSequence
{
	std::tuple<ARGS...>  args_;

	ParameterSequence(ARGS ... args)
	: args_({args...})
	{}
};


} //namespace cli
