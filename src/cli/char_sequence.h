#pragma once
#include <cli/output_stream.h>
#include <stdint.h>
#include <algorithm>
#include <string>
#include <tuple>


namespace cli
{


template<char ... ARGS>
struct CharSequence
{
	static const uint8_t buffer[sizeof...(ARGS)];

	static constexpr size_t size()
	{
		return sizeof...(ARGS);
	}
};


template<char ... ARGS>
const uint8_t CharSequence<ARGS...>::buffer[sizeof...(ARGS)] = {ARGS...};


} //namespace cli
