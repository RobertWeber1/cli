#pragma once
#include <cli/output_stream.h>
#include <cli/char_sequence.h>
#include <cli/parameter_sequence.h>

namespace cli
{


template<class T>
OutputStream<T> & operator<<(OutputStream<T> & stream, Flush)
{
	stream.flush();
	return stream;
}


template<class T, char ... ARGS>
OutputStream<T> & operator<<(
	OutputStream<T> & stream,
	CharSequence<ARGS...> const& val)
{
	using Val = CharSequence<ARGS...>;
	stream.head = std::copy(Val::buffer, Val::buffer+Val::size(), stream.head);
	return stream;
}


template<class T, char CMD, class SEQ, class ... ARGS>
OutputStream<T> & operator<<(
	OutputStream<T> & stream,
	ParameterSequence<CMD, SEQ, ARGS...> const& val)
{
	return stream;
}


} //namespace cli
