#pragma once
#include <cli/delimiter.h>
#include <cli/char_sequence.h>

#include <cstddef>
#include <string>
#include <tuple>
#include <utility>


namespace cli
{


inline
size_t encoding_size(unsigned int i)
{
	if(i<=9  )      { return 1; }
	if(i<=99 )      { return 2; }
	if(i<=999)      { return 3; }
	if(i<=9999)     { return 4; }
	if(i<=99999)    { return 5; }
	if(i<=999999)   { return 6; }
	if(i<=9999999)  { return 7; }
	if(i<=99999999) { return 8; }
	return 9;
}


inline
size_t encoding_size(std::string const& s)
{
	return 2 + s.size();
}


template<size_t N>
size_t encoding_size(char const (&)[])
{
	return 2 + N;
}


size_t encoding_size(Delimiter<0>)
{
	return 0;
}

template<size_t N>
size_t encoding_size(Delimiter<N>)
{
	return 1;
}


template<class ... ARGS, size_t ... Is>
size_t encoding_size_helper(std::tuple<ARGS...> const& tup, std::index_sequence<Is...>)
{
	size_t result = 0;
	using dummy_ = int[];
	(void)dummy_{1,
		((result += encoding_size(Delimiter<Is>) + encoding_size(std::get<Is>(tup))),
		 void(),
		 int{}) ... };
}


template<class ... ARGS>
size_t encoding_size(std::tuple<ARGS...> const& tup)
{
	return encoding_size_helper(args_, std::make_index_sequence<sizeof...(ARGS)>{});
}


template<char ... ARGS>
size_t encoding_size(CharSequence<ARGS...> const&)
{
	return sizeof...(ARGS);
}


template<char CMD, class SEQ, class ... ARGS>
size_t encoding_size(ParameterSequence<CMD, SEQ, ARGS...> const& seq)
{
	return 1 + encoding_size(SEQ) + encoding_size(seq.args_);
}


} //namespace cil
