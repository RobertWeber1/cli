#include "hlayout.h"
#include <iomanip>


HLayout::HLayout(const LayoutObject::SizeHint & sizeHint, bool drawBorder) :
	LayoutObject(drawBorder, sizeHint, H_LAYOUT),
	Layout()
{}


HLayout::~HLayout()
{}


void HLayout::setSize(unsigned int columnOffset,
                      unsigned int lineOffset, 
                      unsigned int width, 
                      unsigned int height)
{
	this->width = width;
	this->height = height;
	
	
	if(objects.size() > 0)
	{
		//when borders collapse, more space is available
		if(objects.size() > 1)
		{
			width += objects.size() -1;
		}


		LayoutObject::SizeHint currentHint = calcSizeHint();

		//calc new LayoutObject width
		std::vector<LayoutObject::SizeConstraint> newWidths;

		unsigned int usedWidth = 0;

		for(std::vector<LayoutObject*>::iterator it = objects.begin(); 
		    it != objects.end(); it++)
		{
			newWidths.push_back((*it)->getSizeHint().width);
			usedWidth += (*it)->getSizeHint().width.minVal;
		}

		while(usedWidth < width)
		{
			unsigned int unusedWidth = width - usedWidth;
			unsigned int globalGrow = 0;
			for(unsigned int i=0; i<newWidths.size(); i++)
			{
				unsigned int growVal = 0;
				growVal = newWidths[i].grow(newWidths[i].minVal, 
				                            unusedWidth, 
				                            currentHint.width.factor);
				if((globalGrow + growVal) > unusedWidth)
				{
					growVal = unusedWidth - globalGrow;
				}
				newWidths[i].minVal += growVal;
				globalGrow += growVal;

			}
			usedWidth += globalGrow;
			if(globalGrow == 0)
			{
				//give unused spase to last object
				newWidths[newWidths.size()-1].minVal += usedWidth;
				break;
			}
		}

		//std::cout << "max width: " <<  width << ", max height: " << height << std::endl;
		//assign new width
		for(unsigned int i=0; i<newWidths.size(); i++)
		{
			//std::cout << "new width: " <<  newWidths[i].minVal << ", new height: " << height << std::endl;
			// if(i==0)
			// {
			// 	objects[i]->setSize(newWidths[i].minVal, height);
			// }
			// else
			// {
				objects[i]->setSize(columnOffset,
					                lineOffset, 
					                newWidths[i].minVal, 
					                height);
				columnOffset += newWidths[i].minVal - 1;
			//}
		}
	}
}


void HLayout::toStream(std::ostream & os) const
{
	for(std::vector<LayoutObject*>::const_iterator it = objects.begin(); 
	    it != objects.end(); it++)
	{
		(*it)->toStream(os);
	}
	//if(lineIndex < height)
	//{
		// if(objects.size() == 0)
		// {
		// 	if(lineIndex == 0)
		// 	{
		// 		os << border.topLeft << std::setw(width - 2) 
		// 		   << std::setfill(border.top) << border.top << border.topRight;
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
		// 		//os << border.bottomLeft << std::setw(width - 2) 
		// 		//   << std::setfill(border.bottom) << border.bottom << border.bottomRight;
		// 	}
		// 	else
		// 	{
		// 		os << border.left << std::setw(width - 2) 
		// 		   << std::setfill(' ') << " " << border.right;
		// 	}
		// }
		// else
		// {
			//for(std::vector<LayoutObject*>::const_iterator it = objects.begin(); 
			//    it != objects.end(); it++)
			//{
				//std::vector<LayoutObject*>::const_iterator itt = it+1;
				//if(objects.size() == 1)
				//{
				//	(*it)->toStream(os, lineIndex, border);
				// }
				// else
				// {
				// 	if(itt == objects.end())
				// 	{
				// 		(*it)->toStream(os, lineIndex, border);
				// 	}
				// 	else
				// 	{
				// 		(*it)->toStream(os, lineIndex);//, Border(border.topLeft, 
				//                                       // border.top, 
				//                                       // 0, 
				//                                       // border.left, 
				//                                       // 0, 
				//                                       // border.bottomLeft, 
				//                                       // border.bottom, 
				//                                       // 0));
				// 	}
				// }
			//}
		// }
	//}
}


LayoutObject::SizeHint HLayout::calcSizeHint()
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
			result.width.add((*it)->getSizeHint().width);
			result.height.max((*it)->getSizeHint().height);
		}
	}

	return result;
}

void HLayout::borderToBuffer(BorderBuffer& buffer)
{
	for(std::vector<LayoutObject*>::const_iterator it = objects.begin(); 
	    it != objects.end(); it++)
	{
		(*it)->borderToBuffer(buffer);
	}
}