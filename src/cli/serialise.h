#pragma once
#include <cli/delimiter.h>
#include <cli/output_stream.h>
#include <cli/char_sequence.h>
#include <cli/parameter_sequence.h>
#include <cli/types.h>
#include <type_traits>

namespace cli
{


template<class T>
OutputStream<T> & operator<<(OutputStream<T> & stream, Flush)
{
	stream.flush();
	return stream;
}


//----------------------------------------------------------------------------//


template<class T, char ... ARGS>
OutputStream<T> & operator<<(
	OutputStream<T> & stream,
	CharSequence<ARGS...> const& val)
{
	using Val = CharSequence<ARGS...>;
	stream.head = std::copy(Val::buffer, Val::buffer+Val::size(), stream.head);
	return stream;
}


//----------------------------------------------------------------------------//


template<class T>
OutputStream<T> & operator<<(OutputStream<T> & stream, unsigned int val)
{
	*stream.head = '0';
	if(val == 0)
	{
		stream.head++;
		return stream;
	}

    uint8_t* p_first = stream.head;
    while( val != 0 )
    {
        *stream.head++ = '0' + val % 10;
        val /= 10;
    }
    std::reverse( p_first, stream.head );

	return stream;
}


template<class T, class ENUM>
typename std::enable_if<std::is_enum<ENUM>::value, OutputStream<T>&>::type
	operator<<(OutputStream<T> & stream, ENUM val)
{
	return stream << static_cast<unsigned int>(val);
}


//----------------------------------------------------------------------------//


template<class T>
OutputStream<T> & operator<<(OutputStream<T> & stream, std::string const& val)
{
	*stream.head++ = '\"';
	stream.head = std::copy(std::begin(val), std::end(val), stream.head);
	*stream.head++ = '\"';
	return stream;
}


//----------------------------------------------------------------------------//


template<class T, size_t N>
OutputStream<T> & operator<<(OutputStream<T> & stream, char const(& val)[N])
{
	*stream.head++ = '\"';
	stream.head = std::copy(std::begin(val), std::end(val)-1, stream.head);
	*stream.head++ = '\"';
	return stream;
}


//----------------------------------------------------------------------------//


template<class T, class REP, class TAG, template<class> class ... SKILLS>
OutputStream<T> & operator<<(
	OutputStream<T> & stream,
	Type<REP, TAG, SKILLS...> const& type)
{
	return stream << type.value;
}


template<class T, class REP, class TAG, class AFFINE_TO_TAG>
OutputStream<T> & operator<<(
	OutputStream<T> & stream,
	AffineType<REP, TAG, AFFINE_TO_TAG> const& type)
{
	return stream << type.value;
}


//----------------------------------------------------------------------------//

template<class T>
OutputStream<T> & operator<<(OutputStream<T> & stream, Delimiter<0>)
{
	return stream;
}

template<class T, size_t N>
OutputStream<T> & operator<<(OutputStream<T> & stream, Delimiter<N>)
{
	*stream.head++ = ';';
	return stream;
}


//----------------------------------------------------------------------------//


template<class T, class ... ARGS, size_t ... Is>
void encode_helper(OutputStream<T> & stream, std::tuple<ARGS...> const& tup, std::index_sequence<Is...>)
{
	using dummy_ = int[];
	(void)dummy_{1, ((stream << Delimiter<Is>{} << std::get<Is>(tup)), void(), int{})... };
}


template<class T, char CMD, class SEQ, class ... ARGS>
OutputStream<T> & operator<<(
	OutputStream<T> & stream,
	ParameterSequence<CMD, SEQ, ARGS...> const& val)
{
	stream << SEQ{};

	encode_helper(stream, val.args_, std::make_index_sequence<sizeof...(ARGS)>{});

	stream << CharSequence<CMD>{};
	return stream;
}


} //namespace cli
