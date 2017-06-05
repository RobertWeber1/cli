#include "vertical_layout.h"
#include <iostream>

namespace CLI
{

namespace layout
{


VerticalLayout::VerticalLayout( const util::SizeHint & size_hint )
: LayoutObject( size_hint, V_LAYOUT )
, Layout()
{}


VerticalLayout::~VerticalLayout()
{}


void VerticalLayout::size( util::Point const& position, util::Size const& size )
{
 	_size = size;

	if(objects.size() > 0)
	{
		//when borders collapse, more space is available
		if(objects.size() > 1)
		{
			_size.height( _size.height() + objects.size() -1 );
		}

		util::SizeHint currentHint = calc_size_hint();

	// 	//calc new LayoutObject height
		std::vector<util::SizeConstraint> newHeights;

		unsigned int usedHeight = 0;

		for(std::vector<LayoutObject*>::iterator it = objects.begin();
		    it != objects.end(); it++)
		{
			newHeights.push_back((*it)->size_hint().height());
			usedHeight += (*it)->size_hint().height().min_val();
		}
		while(usedHeight < _size.height())
		{
			unsigned int unusedHeight = _size.height() - usedHeight;
			unsigned int globalGrow = 0;
			for(unsigned int i=0; i<newHeights.size(); i++)
			{
				unsigned int growVal = 0;
				growVal = newHeights[i].grow(newHeights[i].min_val(),
				                             unusedHeight,
				                             currentHint.height().factor());
				if((globalGrow + growVal) > unusedHeight)
				{
					growVal = unusedHeight - globalGrow;
				}

				newHeights[i].min_val( newHeights[i].min_val() + growVal );
				globalGrow += growVal;
			}

			usedHeight += globalGrow;

			if(globalGrow = 0)
			{
				//TODO:grow last object
				newHeights[newHeights.size()-1].min_val( newHeights[newHeights.size()-1].min_val() + usedHeight);
				break;
			}
		}

		//assign new height
		util::Point pos = position;
		for(unsigned int i=0; i<newHeights.size(); i++)
		{
			objects[i]->size( pos, util::Size(_size.width(), newHeights[i].min_val()) );
			pos.down(newHeights[i].min_val() - 1);
		}
	}
}


void VerticalLayout::border_to_buffer( border::Buffer& buffer )
{
	for(std::vector<LayoutObject*>::const_iterator it = objects.begin();
	    it != objects.end(); it++)
	{
		(*it)->border_to_buffer( buffer );
	}
}


util::SizeHint VerticalLayout::calc_size_hint()
{
	util::SizeHint result;

	if(objects.size() == 0)
	{
		result = _default_size_hint;
	}
	else
	{
		for(std::vector<LayoutObject*>::iterator it = objects.begin();
		    it != objects.end(); it++)
		{
			result.width().max( (*it)->size_hint().width() );
			result.height().add( (*it)->size_hint().height() );
		}
	}

	return result;
}


}// namespace layout

} // namespace CLI
