#include "unitTests.h"
#include "border/element.h"
#include "border/buffer.h"
#include "testUtils.h"
#include <iostream>

using namespace CLI;
using namespace border;
using namespace util;

char char_map[16] = {
	' ',//NONE         = 0b00000,
	'0',//UNUSED_1     = 0b00001,
	'0',//UNUSED_2     = 0b00010,
	'7',//BOTTOM_LEFT  = 0b00011,
	'0',//UNUSED_4     = 0b00100,
	'|',//VERTICAL     = 0b00101,
	'1',//TOP_LEFT     = 0b00110,
	'8',//TEE_RIGHT    = 0b00111,
	'0',//UNUSED_8     = 0b01000,
	'5',//BOTTOM_RIGHT = 0b01001,
	'-',//HORIZONTAL   = 0b01010,
	'6',//TEE_TOP      = 0b01011,
	'3',//TOP_RIGHT    = 0b01100,
	'4',//TEE_LEFT     = 0b01101,
	'2',//TEE_BOTTOM   = 0b01110,
	'+' //CROSS        = 0b01111,
};


void element_convertToVisibleChar(std::pair<unsigned int, unsigned int> & result)
{
	Element none(Element::NONE);
	Element top_left(Element::TOP_LEFT);
	Element horizontal(Element::HORIZONTAL);
	Element top_right(Element::TOP_RIGHT);
	Element vertical(Element::VERTICAL);
	Element bottom_left(Element::BOTTOM_LEFT);
	Element bottom_right(Element::BOTTOM_RIGHT);
	Element tee_left(Element::TEE_LEFT);
	Element tee_right(Element::TEE_RIGHT);
	Element tee_bottom(Element::TEE_BOTTOM);
	Element tee_top(Element::TEE_TOP);
	Element cross(Element::CROSS);

	check(std::string(__FUNCTION__)+" none", none.to_char(char_map), ' ', result);
	check(std::string(__FUNCTION__)+" top_left", top_left.to_char(char_map), '1', result);
	check(std::string(__FUNCTION__)+" horizontal", horizontal.to_char(char_map), '-', result);
	check(std::string(__FUNCTION__)+" top_right", top_right.to_char(char_map), '3', result);
	check(std::string(__FUNCTION__)+" vertical", vertical.to_char(char_map), '|', result);
	check(std::string(__FUNCTION__)+" bottom_left", bottom_left.to_char(char_map), '7', result);
	check(std::string(__FUNCTION__)+" bottom_right", bottom_right.to_char(char_map), '5', result);
	check(std::string(__FUNCTION__)+" tee_left", tee_left.to_char(char_map), '4', result);
	check(std::string(__FUNCTION__)+" tee_right", tee_right.to_char(char_map), '8', result);
	check(std::string(__FUNCTION__)+" tee_bottom", tee_bottom.to_char(char_map), '2', result);
	check(std::string(__FUNCTION__)+" tee_top", tee_top.to_char(char_map), '6', result);
	check(std::string(__FUNCTION__)+" cross", cross.to_char(char_map), '+', result);
}


void invertedelement_convertToVisibleChar(std::pair<unsigned int, unsigned int> & result)
{
	Element inv_none((uint8_t)Element::NONE|(uint8_t)Element::INVERT);
	Element inv_top_left((uint8_t)Element::TOP_LEFT|(uint8_t)Element::INVERT);
	Element inv_horizontal((uint8_t)Element::HORIZONTAL|(uint8_t)Element::INVERT);
	Element inv_top_right((uint8_t)Element::TOP_RIGHT|(uint8_t)Element::INVERT);
	Element inv_vertical((uint8_t)Element::VERTICAL|(uint8_t)Element::INVERT);
	Element inv_bottom_left((uint8_t)Element::BOTTOM_LEFT|(uint8_t)Element::INVERT);
	Element inv_bottom_right((uint8_t)Element::BOTTOM_RIGHT|(uint8_t)Element::INVERT);
	Element inv_tee_left((uint8_t)Element::TEE_LEFT|(uint8_t)Element::INVERT);
	Element inv_tee_right((uint8_t)Element::TEE_RIGHT|(uint8_t)Element::INVERT);
	Element inv_tee_bottom((uint8_t)Element::TEE_BOTTOM|(uint8_t)Element::INVERT);
	Element inv_tee_top((uint8_t)Element::TEE_TOP|(uint8_t)Element::INVERT);
	Element inv_cross((uint8_t)Element::CROSS|(uint8_t)Element::INVERT);

	check(std::string(__FUNCTION__)+" inv_none", inv_none.to_char(char_map), ' ', result);
	check(std::string(__FUNCTION__)+" inv_top_left", inv_top_left.to_char(char_map), '1', result);
	check(std::string(__FUNCTION__)+" inv_horizontal", inv_horizontal.to_char(char_map), '-', result);
	check(std::string(__FUNCTION__)+" inv_top_right", inv_top_right.to_char(char_map), '3', result);
	check(std::string(__FUNCTION__)+" inv_vertical", inv_vertical.to_char(char_map), '|', result);
	check(std::string(__FUNCTION__)+" inv_bottom_left", inv_bottom_left.to_char(char_map), '7', result);
	check(std::string(__FUNCTION__)+" inv_bottom_right", inv_bottom_right.to_char(char_map), '5', result);
	check(std::string(__FUNCTION__)+" inv_tee_left", inv_tee_left.to_char(char_map), '4', result);
	check(std::string(__FUNCTION__)+" inv_tee_right", inv_tee_right.to_char(char_map), '8', result);
	check(std::string(__FUNCTION__)+" inv_tee_bottom", inv_tee_bottom.to_char(char_map), '2', result);
	check(std::string(__FUNCTION__)+" inv_tee_top", inv_tee_top.to_char(char_map), '6', result);
	check(std::string(__FUNCTION__)+" inv_cross", inv_cross.to_char(char_map), '+', result);
}


void element_addingTopLeftToNone_resultIsTopLeft(std::pair<unsigned int, unsigned int> & result)
{
	Element none(Element::NONE);
	Element top_left(Element::TOP_LEFT);

	check(__FUNCTION__, none.add(top_left).type(), Element::TOP_LEFT, result);
}


void element_addingTopLeftToTopRight_resultIsTeeBottom(std::pair<unsigned int, unsigned int> & result)
{
	Element top_left(Element::TOP_LEFT);
	Element top_right(Element::TOP_RIGHT);

	check(__FUNCTION__, top_left.add(top_right).type(), Element::TEE_BOTTOM, result);
}


void element_addingTopLeftToBottomRight_resultIsCross(std::pair<unsigned int, unsigned int> & result)
{
	Element top_left(Element::TOP_LEFT);
	Element bottom_right(Element::BOTTOM_RIGHT);

	check(__FUNCTION__, top_left.add(bottom_right).type(), Element::CROSS, result);
}


void element_addingHorizontalToVertical_resultIsCross(std::pair<unsigned int, unsigned int> & result)
{
	Element vertical(Element::VERTICAL);
	check(__FUNCTION__, vertical.add(Element::HORIZONTAL).type(), Element::CROSS, result);
}


void element_subtractHorizontalFromCross_resultIsVertical(std::pair<unsigned int, unsigned int> & result)
{
	Element cross(Element::CROSS);
	check(__FUNCTION__, cross.remove(Element::HORIZONTAL).type(), Element::VERTICAL, result);
}


void element_subtractHorizontalAndVerticalFromCross_resultIsNone(std::pair<unsigned int, unsigned int> & result)
{
	Element cross(Element::CROSS);
	check(__FUNCTION__, cross.remove(Element::HORIZONTAL).remove(Element::VERTICAL).type(), Element::NONE, result);
}


//----------------------------------------------------------------------------//


void buffer_create100x100_sizeIs100x100(std::pair<unsigned int, unsigned int> & result)
{
	Buffer buffer(util::Size(100,100));

	check(__FUNCTION__, to_string(buffer.size()), std::string("S(w: 100, h: 100)"), result);
}


void buffer_create10x10Max100x123_resizeTo1000x1234_sizeIs100x100(std::pair<unsigned int, unsigned int> & result)
{
	Buffer buffer(util::Size(10,10), util::Size(100,123));

	buffer.resize(Size(1000, 1234));

	check(__FUNCTION__, to_string(buffer.size()), std::string("S(w: 100, h: 123)"), result);
}


void buffer_renderUnusedBuffer_resultIsBlank(std::pair<unsigned int, unsigned int> & result)
{
	Buffer buffer( Size(10, 10) );

	char char_map[16] = { '0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};
	std::stringstream borders;
	Point pos( 0, 0 );
	Element *element;
	while( element = buffer.get( pos ) )
	{
		while( element = buffer.get( pos ) )
		{
			borders << element->to_char(char_map);
			pos.right();
		}
		borders << "\n";
		pos.break_line();
	}

	check(__FUNCTION__, borders.str(), std::string("0000000000\n0000000000\n0000000000\n0000000000\n0000000000\n0000000000\n0000000000\n0000000000\n0000000000\n0000000000\n"), result);
}


void buffer_render4x4BorderAt1x2(std::pair<unsigned int, unsigned int> & result)
{
	Buffer buffer( Size(10, 10) );
	Size size( 4, 4 );
	Point p1 ( 1, 2 );

	buffer.draw( p1, size );

	check(__FUNCTION__, to_string(buffer), std::string(
"          \n\
          \n\
 1--3     \n\
 |  |     \n\
 |  |     \n\
 7--5     \n\
          \n\
          \n\
          \n\
          \n"), result);
}


void buffer_render4OverlappingBorders(std::pair<unsigned int, unsigned int> & result)
{
	Buffer buffer( Size(10, 10) );
	Size size( 4, 4 );
	Point p1 ( 1, 2 );
	Point p2 ( 4, 2 );
	Point p3 ( 1, 5 );
	Point p4 ( 4, 5 );

	buffer.draw( p1, size );
	buffer.draw( p2, size );
	buffer.draw( p3, size );
	buffer.draw( p4, size );

	check(__FUNCTION__, to_string(buffer), std::string(
"          \n\
          \n\
 1--2--3  \n\
 |  |  |  \n\
 |  |  |  \n\
 8--+--4  \n\
 |  |  |  \n\
 |  |  |  \n\
 7--6--5  \n\
          \n"), result);
}


void buffer_render4OverlappingBordersRemoveOne(std::pair<unsigned int, unsigned int> & result)
{
	Buffer buffer( Size(10, 10) );
	Size size( 4, 4 );
	Point p1 ( 1, 2 );
	Point p2 ( 4, 2 );
	Point p3 ( 1, 5 );
	Point p4 ( 4, 5 );
	buffer.draw( p1, size );
	buffer.draw( p2, size );
	buffer.draw( p3, size );
	buffer.draw( p4, size );

	buffer.draw( p4, size, Buffer::Remove );

	check(__FUNCTION__, to_string(buffer), std::string(
"          \n\
          \n\
 1--2--3  \n\
 |  |  |  \n\
 |  |  |  \n\
 8--+--5  \n\
 |  |     \n\
 |  |     \n\
 7--5     \n\
          \n"), result);
}


void buffer_render4OverlappingBordersRemoveTwo(std::pair<unsigned int, unsigned int> & result)
{
	Buffer buffer( Size(10, 10) );
	Size size( 4, 4 );
	Point p1 ( 1, 2 );
	Point p2 ( 4, 2 );
	Point p3 ( 1, 5 );
	Point p4 ( 4, 5 );
	buffer.draw( p1, size );
	buffer.draw( p2, size );
	buffer.draw( p3, size );
	buffer.draw( p4, size );

	buffer.draw( p3, size, Buffer::Remove );
	buffer.draw( p4, size, Buffer::Remove );

	check(__FUNCTION__, to_string(buffer), std::string(
"          \n\
          \n\
 1--2--3  \n\
 |  |  |  \n\
 |  |  |  \n\
 7--6--5  \n\
          \n\
          \n\
          \n\
          \n"), result);
}


void buffer_render4OverlappingBordersTowAreInverted(std::pair<unsigned int, unsigned int> & result)
{
	Buffer buffer( Size(10, 10) );
	Size size( 4, 4 );
	Point p1 ( 1, 2 );
	Point p2 ( 4, 2 );
	Point p3 ( 1, 5 );
	Point p4 ( 4, 5 );

	buffer.draw( p1, size, Buffer::Add, Buffer::DrawInverted );
	buffer.draw( p2, size );
	buffer.draw( p3, size );
	buffer.draw( p4, size, Buffer::Add, Buffer::DrawInverted );

	check(__FUNCTION__, to_string(buffer), std::string(
"          \n\
          \n\
 A==B--3  \n\
 #  #  |  \n\
 #  #  |  \n\
 H==\%==D  \n\
 |  #  #  \n\
 |  #  #  \n\
 7--F==E  \n\
          \n"), result);
}


void buffer_render4OverlappingBordersTowAreInvertedRemoveOneInverted(std::pair<unsigned int, unsigned int> & result)
{
	Buffer buffer( Size(10, 10) );
	Size size( 4, 4 );
	Point p1 ( 1, 2 );
	Point p2 ( 4, 2 );
	Point p3 ( 1, 5 );
	Point p4 ( 4, 5 );
	buffer.draw( p1, size, Buffer::Add, Buffer::DrawInverted );
	buffer.draw( p2, size );
	buffer.draw( p3, size );
	buffer.draw( p4, size, Buffer::Add, Buffer::DrawInverted );

	buffer.draw( p1, size, Buffer::Remove, Buffer::DrawInverted );

	check(__FUNCTION__, to_string(buffer), std::string(
"          \n\
          \n\
    1--3  \n\
    |  |  \n\
    |  |  \n\
 1--\%==D  \n\
 |  #  #  \n\
 |  #  #  \n\
 7--F==E  \n\
          \n"), result);
}


void buffer_render4OverlappingBordersTowAreInvertedRemoveTwoInverted(std::pair<unsigned int, unsigned int> & result)
{
	Buffer buffer( Size(10, 10) );
	Size size( 4, 4 );
	Point p1 ( 1, 2 );
	Point p2 ( 4, 2 );
	Point p3 ( 1, 5 );
	Point p4 ( 4, 5 );
	buffer.draw( p1, size, Buffer::Add, Buffer::DrawInverted );
	buffer.draw( p2, size );
	buffer.draw( p3, size );
	buffer.draw( p4, size, Buffer::Add, Buffer::DrawInverted );

	buffer.draw( p1, size, Buffer::Remove, Buffer::DrawInverted );
	buffer.draw( p4, size, Buffer::Remove, Buffer::DrawInverted );

	check(__FUNCTION__, to_string(buffer), std::string(
"          \n\
          \n\
    1--3  \n\
    |  |  \n\
    |  |  \n\
 1--+--5  \n\
 |  |     \n\
 |  |     \n\
 7--5     \n\
          \n"), result);
}


//----------------------------------------------------------------------------//


std::pair<unsigned int, unsigned int> border_unit_test()
{
	std::pair<unsigned int, unsigned int> result(0,0);

	element_convertToVisibleChar(result);
	invertedelement_convertToVisibleChar(result);
	element_addingTopLeftToNone_resultIsTopLeft(result);
	element_addingTopLeftToTopRight_resultIsTeeBottom(result);
	element_addingTopLeftToBottomRight_resultIsCross(result);
	element_addingHorizontalToVertical_resultIsCross(result);
	element_subtractHorizontalFromCross_resultIsVertical(result);
	element_subtractHorizontalAndVerticalFromCross_resultIsNone(result);

	buffer_create100x100_sizeIs100x100(result);
	buffer_create10x10Max100x123_resizeTo1000x1234_sizeIs100x100(result);
	buffer_renderUnusedBuffer_resultIsBlank(result);
	buffer_render4x4BorderAt1x2(result);
	buffer_render4OverlappingBorders(result);
	buffer_render4OverlappingBordersRemoveOne(result);
	buffer_render4OverlappingBordersRemoveTwo(result);
	buffer_render4OverlappingBordersTowAreInverted(result);
	buffer_render4OverlappingBordersTowAreInvertedRemoveOneInverted(result);
	buffer_render4OverlappingBordersTowAreInvertedRemoveTwoInverted(result);

	return result;
}
