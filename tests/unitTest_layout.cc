#include "unitTests.h"
#include "layout/vertical_layout.h"
#include "layout/horizontal_layout.h"
#include "util/size_constraint.h"
#include "border/buffer.h"
#include "testUtils.h"
#include <iostream>

using namespace CLI;
using namespace border;
using namespace layout;
using namespace util;

class Dummy : public LayoutObject
{
public:
	Dummy( util::SizeHint const& size_hint = util::SizeHint( ) )
	: LayoutObject( size_hint, LayoutObject::WIDGET )
	{}

	void size( util::Point const& position, util::Size const& size )
	{
		_size = size;
		_position = position;
	}

	void border_to_buffer( border::Buffer& buffer )
	{
		buffer.draw(_position, _size);
	}

	virtual util::SizeHint calc_size_hint()
	{
		return _default_size_hint;
	}

	util::Point _position;
};

void verticalLayout_containsSingleObject(std::pair<unsigned int, unsigned int> & result)
{
	Buffer buffer( Size(10, 10) );
	VerticalLayout vertical;
	Dummy dummy;
	vertical.add( &dummy );
	vertical.size( Point(0, 0),  Size(10, 10) );

	vertical.border_to_buffer( buffer );

	check(__FUNCTION__, to_string(buffer), std::string(
"1--------3\n\
|        |\n\
|        |\n\
|        |\n\
|        |\n\
|        |\n\
|        |\n\
|        |\n\
|        |\n\
7--------5\n"), result);
}

void verticalLayout_containsTwoEqualSizedObjects(std::pair<unsigned int, unsigned int> & result)
{
	Buffer buffer( Size(10, 10) );
	VerticalLayout vertical;
	Dummy dummy;
	Dummy dummy2;
	vertical.add( &dummy );
	vertical.add( &dummy2 );
	vertical.size( Point(0, 0),  Size(10, 10) );

	vertical.border_to_buffer( buffer );

	check(__FUNCTION__, to_string(buffer), std::string(
"1--------3\n\
|        |\n\
|        |\n\
|        |\n\
|        |\n\
8--------4\n\
|        |\n\
|        |\n\
|        |\n\
7--------5\n"), result);

}


void verticalLayout_containsTreeObjectsTwoMinimalSize(std::pair<unsigned int, unsigned int> & result)
{
	Buffer buffer( Size(10, 10) );
	VerticalLayout vertical;
	Dummy dummy( util::SizeHint( util::SizeConstraint(), util::SizeConstraint(3,3,1) ) );
	Dummy dummy2;
	Dummy dummy3( util::SizeHint( util::SizeConstraint(), util::SizeConstraint(3,3,1) ) );

	vertical.add( &dummy );
	vertical.add( &dummy2 );
	vertical.add( &dummy3 );
	vertical.size( Point(0, 0),  Size(10, 10) );

	vertical.border_to_buffer( buffer );

	check(__FUNCTION__, to_string(buffer), std::string(
"1--------3\n\
|        |\n\
8--------4\n\
|        |\n\
|        |\n\
|        |\n\
|        |\n\
8--------4\n\
|        |\n\
7--------5\n"), result);

}

void horizontalLayout_containsTreeObjectsTwoMinimalSize(std::pair<unsigned int, unsigned int> & result)
{
	Buffer buffer( Size(10, 10) );
	HorizontalLayout horizontal;
	Dummy dummy( util::SizeHint( util::SizeConstraint(3,3,1), util::SizeConstraint() ) );
	Dummy dummy2;
	Dummy dummy3( util::SizeHint( util::SizeConstraint(3,3,1), util::SizeConstraint() ) );

	horizontal.add( &dummy );
	horizontal.add( &dummy2 );
	horizontal.add( &dummy3 );
	horizontal.size( Point(0, 0),  Size(10, 10) );

	horizontal.border_to_buffer( buffer );

	check(__FUNCTION__, to_string(buffer), std::string(
"1-2----2-3\n\
| |    | |\n\
| |    | |\n\
| |    | |\n\
| |    | |\n\
| |    | |\n\
| |    | |\n\
| |    | |\n\
| |    | |\n\
7-6----6-5\n"), result);

}


void horizontalVerticalLayout_containsvariousObjects(std::pair<unsigned int, unsigned int> & result)
{
	Buffer buffer( Size(10, 10) );
	VerticalLayout vertical;
	HorizontalLayout horizontal;
	Dummy dummy( util::SizeHint( util::SizeConstraint(), util::SizeConstraint(3,3,1) ) );
	Dummy dummy2( util::SizeHint( util::SizeConstraint(), util::SizeConstraint(3,3,1) ) );
	Dummy dummy3;
	Dummy dummy4;

	vertical.add( &dummy );
	vertical.add( &horizontal );
	vertical.add( &dummy2 );

	horizontal.add( &dummy3 );
	horizontal.add( &dummy4 );


	vertical.size( Point(0, 0),  Size(10, 10) );

	vertical.border_to_buffer( buffer );

	check(__FUNCTION__, to_string(buffer), std::string(
"1--------3\n\
|        |\n\
8----2---4\n\
|    |   |\n\
|    |   |\n\
|    |   |\n\
|    |   |\n\
8----6---4\n\
|        |\n\
7--------5\n"), result);

}

std::pair<unsigned int, unsigned int> layout_unit_test()
{
	std::pair<unsigned int, unsigned int> result(0,0);

	verticalLayout_containsSingleObject(result);
	verticalLayout_containsTwoEqualSizedObjects(result);
	verticalLayout_containsTreeObjectsTwoMinimalSize(result);

	horizontalLayout_containsTreeObjectsTwoMinimalSize(result);

	horizontalVerticalLayout_containsvariousObjects(result);
	return result;
}