#pragma once

namespace CLI
{

namespace util
{

class Size
{
public:
	Size( unsigned int width = 0, unsigned int height = 0 );

	unsigned int width() const;

	void width( unsigned int new_width );

	unsigned int height() const;

	void height( unsigned int new_height );

	void zero();

	Size trim( Size const& max_size ) const;

private:
	unsigned int _width;
	unsigned int _height;
};

} //namespace util

} //namespace CLI
