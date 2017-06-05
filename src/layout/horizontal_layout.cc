#include "horizontal_layout.h"
#include <iostream>

namespace CLI
{

namespace layout
{


HorizontalLayout::HorizontalLayout( const util::SizeHint & size_hint )
: LayoutObject( size_hint, V_LAYOUT )
, Layout()
{}


HorizontalLayout::~HorizontalLayout()
{}


void HorizontalLayout::size( util::Point const& position, util::Size const& size )
{
 	_size = size;

	if(objects.size() > 0)
	{
		//when borders collapse, more space is available
		if(objects.size() > 1)
		{
			_size.width( _size.width() + objects.size() -1 );
		}

		util::SizeHint current_hint = calc_size_hint();

	// 	//calc new LayoutObject width
		std::vector<util::SizeConstraint> new_width;

		unsigned int used_width = 0;

		for(std::vector<LayoutObject*>::iterator it = objects.begin();
		    it != objects.end(); it++)
		{
			new_width.push_back((*it)->size_hint().width());
			used_width += (*it)->size_hint().width().min_val();
		}
		while(used_width < _size.width())
		{
			unsigned int unused_width = _size.width() - used_width;
			unsigned int globalGrow = 0;
			for(unsigned int i=0; i<new_width.size(); i++)
			{
				unsigned int growVal = 0;
				growVal = new_width[i].grow(new_width[i].min_val(),
				                             unused_width,
				                             current_hint.width().factor());
				if((globalGrow + growVal) > unused_width)
				{
					growVal = unused_width - globalGrow;
				}

				new_width[i].min_val( new_width[i].min_val() + growVal );
				globalGrow += growVal;
			}

			used_width += globalGrow;

			if(globalGrow = 0)
			{
				//TODO:grow last object
				new_width[new_width.size()-1].min_val( new_width[new_width.size()-1].min_val() + used_width);
				break;
			}
		}

		//assign new width
		util::Point pos = position;
		for(unsigned int i=0; i<new_width.size(); i++)
		{
			objects[i]->size( pos, util::Size(new_width[i].min_val(), _size.height()) );
			pos.right(new_width[i].min_val() - 1);
		}
	}
}


void HorizontalLayout::border_to_buffer( border::Buffer& buffer )
{
	for(std::vector<LayoutObject*>::const_iterator it = objects.begin();
	    it != objects.end(); it++)
	{
		(*it)->border_to_buffer( buffer );
	}
}


util::SizeHint HorizontalLayout::calc_size_hint()
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
			result.width().add( (*it)->size_hint().width() );
			result.height().max( (*it)->size_hint().height() );
		}
	}

	return result;
}


}// namespace layout

} // namespace CLI
