#pragma once

namespace CLI
{

namespace util
{

class Size
{
public:
	Size( unsigned int width = 0, unsigned int height = 0 )
	: _width(width)
	, _height(height)
	{}

	unsigned int width() const
	{
		return _width;
	}

	unsigned int height() const
	{
		return _height;
	}

	void width( unsigned int new_width )
	{
		_width = new_width;
	}

	void height( unsigned int new_height )
	{
		_height = new_height;
	}

	void zero()
	{
		_height = 0;
		_width = 0;
	}

	Size trim( Size const& max_size ) const
	{
		return Size( ( (_width<max_size.width()) ? _width : max_size.width() )
		           , ( (_height<max_size.height()) ? _height : max_size.height() ) );
	}

private:
	unsigned int _width;
	unsigned int _height;
};

} //namespace util

} //namespace CLI
