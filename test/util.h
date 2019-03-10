#pragma once
#include <cli/output_stream.h>
#include <queue>
#include <string>
#include <ostream>
#include <iomanip>

template<class T=std::string>
struct TestResult
{
	std::queue<T> result_;

	T get_result()
	{
		T ret;
		if(not result_.empty())
		{
			ret = result_.front();
			result_.pop();
		}
		return ret;
	}

	void clear_results()
	{
		result_ = std::queue<T>();
	}
};




template<size_t N>
struct HexStr
{
	uint8_t data[N];
};


template <size_t N>
constexpr HexStr<N-1> make_hex(char const (& data)[N])
{
	HexStr<N-1> val{};

	std::copy(data, data+N-1, val.data);
	return val;
}



template<class T, size_t N>
bool operator==(cli::OutputStream<T> const& lhs, HexStr<N> const& rhs)
{
	if(lhs.size() != N)
	{
		return false;
	}

	for(size_t i = 0; i<N; ++i)
	{
		if(lhs.begin[i] != rhs.data[i])
		{
			return false;
		}
	}

	return true;
}


template<size_t N>
std::ostream& operator<<(std::ostream& out, HexStr<N> const& hex_str)
{
	out << "Hex{";
	for(uint8_t const* c=hex_str.data; c<hex_str.data+N; ++c)
	{
		if(c != hex_str.data)
		{
			out << " ";
		}
		out << std::setw(2) << std::setfill('0') << std::hex << uint16_t(*c);
	}
	return out << std::dec << "}";
}



namespace cli
{

template<class T>
std::ostream& operator<<(std::ostream& out, cli::OutputStream<T> const& stream)
{
	out << "Hex{";
	for(uint8_t const* c=stream.begin; c<stream.head; ++c)
	{
		if(c != stream.begin)
		{
			out << " ";
		}
		out << std::setw(2) << std::setfill('0') << std::hex << uint16_t(*c);
	}
	return out << std::dec << "}";
}

}



template<size_t N>
struct TestStream : cli::OutputStream<TestStream<N>>, TestResult<>
{
	using Outstream_t = cli::OutputStream<TestStream<N>>;
	uint8_t buffer[N];

	TestStream()
	: Outstream_t(buffer)
	{}

	size_t flush()
	{
		std::stringstream tmp;
		tmp << *this;
		result_.push(tmp.str());
		return Outstream_t::size();
	}
};

