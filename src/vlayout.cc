#include "vlayout.h"
#include <iomanip>


VLayout::VLayout(const LayoutObject::SizeHint & sizeHint, bool drawBorders) :
	LayoutObject(drawBorders, sizeHint),
	Layout()
{}


VLayout::~VLayout()
{}


void VLayout::setSize(unsigned int width, 
                      unsigned int height,
                      const Border & border)
{
	this->width  = width;
	this->height = height;
	//this->border = border;
	if(objects.size() > 0)
	{
		LayoutObject::SizeHint currentHint = calcSizeHint();

		//calc new LayoutObject height
		std::vector<LayoutObject::SizeConstraint> newHeights;

		unsigned int usedHeight = 0;

		for(std::vector<LayoutObject*>::iterator it = objects.begin(); 
		    it != objects.end(); it++)
		{
			newHeights.push_back((*it)->getSizeHint().height);
			usedHeight += (*it)->getSizeHint().height.minVal;
		}

		while(usedHeight < height)
		{
			unsigned int unusedHeight = height - usedHeight;
			unsigned int globalGrow = 0;
			for(unsigned int i=0; i<newHeights.size(); i++)
			{
				unsigned int growVal = 0;
				growVal = newHeights[i].grow(newHeights[i].minVal, 
				                             unusedHeight, 
				                             currentHint.height.factor);
				if((globalGrow + growVal) > unusedHeight)
				{
					growVal = unusedHeight - globalGrow;
				}

				newHeights[i].minVal += growVal;
				globalGrow += growVal;
			}
			usedHeight += globalGrow;
			if(globalGrow == 0)
			{
				//TODO:grow last object
				newHeights[newHeights.size()-1].minVal += usedHeight;
				break;
			}
		}

		//assign new height
		for(unsigned int i=0; i<newHeights.size(); i++)
		{
			if(i==0)
			{
				objects[i]->setSize(width, newHeights[i].minVal, border);
			}
			else
			{
				objects[i]->setSize(width, newHeights[i].minVal, Border(0, 
						                                                0, 
						                                                0, 
						                                                border.left, 
						                                                border.right, 
						                                                border.bottomLeft, 
						                                                border.bottom, 
						                                                border.bottomRight));
			}
		}
	}
}


void VLayout::toStream(std::ostream & os, 
                       unsigned int lineIndex) const
{
	if(lineIndex < height)
	{
		// if(objects.size() == 0)
		// {
		// 	if(lineIndex == 0)
		// 	{
		// 	    if(border.topLeft != 0)
		// 		{
		// 			os << border.topLeft;
		// 		}
		// 		if(border.top != 0)
		// 		{
		// 			os << std::setw(width - 2) 
		// 			   << std::setfill(border.top) << border.top;
		// 		}
		// 		if(border.topRight != 0)
		// 		{
		// 			os << border.topRight;
		// 		}
		// 	}
		// 	else if(lineIndex == height-1)
		// 	{
		// 		if( border.bottomLeft != 0 || 
		// 		    border.bottom != 0 || 
		// 		    border.bottomRight != 0 )
		// 		{
		// 			if(border.bottomLeft)
		// 			{
		// 				os << border.bottomLeft;
		// 			}
		// 			if(border.bottom)
		// 			{
		// 				os << std::setw(width - 2) 
		// 				   << std::setfill(border.bottom) << border.bottom;
		// 			}
		// 			if(border.bottomRight)
		// 			{
		// 				os << border.bottomRight;
		// 			}
		// 		}
		// 		else
		// 		{
		// 			os << border.left << std::setw(width - 2) 
		// 			   << std::setfill(' ') << " " << border.right;
		// 		}
		// 	}
		// 	else
		// 	{
		// 		os << border.left << std::setw(width - 2) 
		// 		   << std::setfill(' ') << " " << border.right;
		// 	}
		// }
		// else
		// {
			unsigned int offset = 0;
			unsigned int line   = lineIndex;

			for(std::vector<LayoutObject*>::const_iterator it = objects.begin(); 
			    it != objects.end(); it++)
			{
				line -= offset;

				if( line < (*it)->getHeight() )
				{
					// std::vector<LayoutObject*>::const_iterator itt = it+1;
					// if(itt == objects.end())
					// {
						(*it)->toStream(os, line);//, border);
					// }
					// else
					// {
					// 	(*it)->toStream(os, line);//, Border(border.topLeft, 
					// 	                          //       border.top, 
					// 	                          //       border.topRight, 
					// 	                          //       border.left, 
					// 	                          //       border.right, 
					// 	                          //       0, 0, 0));
					// }
					break;
				}
				else
				{
					offset = (*it)->getHeight();
				}
			}
		// }
	}
}


LayoutObject::SizeHint VLayout::calcSizeHint()
{
	LayoutObject::SizeHint result;

	if(objects.size() == 0)
	{
		result = defaultSizeHint;
	}
	else
	{
		for(std::vector<LayoutObject*>::iterator it = objects.begin(); 
		    it != objects.end(); it++)
		{
			result.width.max((*it)->getSizeHint().width);
			result.height.add((*it)->getSizeHint().height);
		}
	}

	return result;
}

void VLayout::borderToBuffer(BorderBuffer& buffer, unsigned int lineOffset, unsigned int columnOffset)
{
	
}
