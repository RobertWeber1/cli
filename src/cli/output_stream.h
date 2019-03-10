#pragma once
#include <stdint.h>
#include <string>

namespace cli
{

struct Flush{};

static const Flush flush;


template<class DERIVED>
struct OutputStream
{
private:

public:
	uint8_t * head;
	uint8_t const * const begin;
	uint8_t const * const end;


	uint32_t size() const
	{
		return head - begin;
	}

	uint32_t capacity() const
	{
		return end - begin;
	}

	uint32_t space() const
	{
		return end - head;
	}

	bool has_capacity(uint32_t size)
	{
		if(size > capacity())
		{
			return false;
		}

		if(size > space())
		{
			head -= derived().flush();
		}

		return true;
	}

	bool advance(uint32_t size)
	{
		if(size < space())
		{
			head += size;
			return true;
		}

		return false;
	}

	size_t flush()
	{
		return derived().flush();
	}
private:
	friend DERIVED;


	OutputStream(uint8_t * data, size_t size)
	: head(data)
	, begin(data)
	, end(data+size)
	{}

	template<size_t N>
	OutputStream(uint8_t (&data)[N])
	: head(data)
	, begin(data)
	, end(data+N)
	{}

	DERIVED & derived()
	{
		return static_cast<DERIVED&>(*this);
	}
};


} //namespace cli