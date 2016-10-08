#include "hlayout.h"
#include "vlayout.h"
#include "border.h"
#include "cliwindow.h"
#include <iostream>
#include <iomanip>

void printBorder(const LayoutObject &l, unsigned int lineCount)
{
	for(unsigned int i = 0; i < lineCount; i++)
	{
		std::stringstream tmp;
		l.toStream(tmp, i);
		if(tmp.str().size() != 0)
		{
			std::cout << std::setw(4) << i << ": " << tmp.str() << std::endl;
		}

	}
}

std::string rulerString(unsigned int width)
{
	std::stringstream result;

	for(unsigned int i=0; i<width; i++)
	{
		result << ((i%10 == 0) ? "!" : ".");
	}

	return result.str();
}

void fillWindow(CLIWindow & w, char filler)
{
	

	for(unsigned int i = 0; i < w.getHeight(); i++)
	{
		std::stringstream number;
		number << i;
		std::stringstream fillStr;
		for(unsigned int j=0; j<w.getWidth()-number.str().size(); j++)
		{
			fillStr << filler;
		}

		w.appendLine(number.str()+fillStr.str());
	}
}

int main(int args, char *argv[])
{
	int result = 0;

	Border border('+', '-', '+', '|', '|', '+', '-', '+', '+', '+', '+');



	// +------------------------+      
	// |1aaaaaaaaaaaaaaaaaaaaaaa|      
	// |2aaaaaaaaaaaaaaaaaaaaaaa|     
	// +--------+-----------+---+
	// |1bbbbbbb|1cccccccccc|1ff|   
	// |bbbbb	+-----------+fff|   
	// |2bbbbbbb|1dddddddddd|fff|   
	// |3bbbbbbb+-----------+2ff|   
	// |4bbbbbbb|1eeeeeeeeee|3ff|   
	// +--------+-----------+---+   
	// |1ggggggggggggggggggggggg|   
	// +------------------------+   
    //

	unsigned int winWidth = 80;
	unsigned int winHeight = 40;

	HLayout horizontal1;
	VLayout vertical1, vertical2;
	//CLIWindow w1, w2, w3, w4, w5, w6, w7;
	CLIWindow w1(LayoutObject::SizeHint(3,winWidth,1, 3,10,2));
	CLIWindow w2(LayoutObject::SizeHint(3,winWidth/3,1, 3,30,2));
	CLIWindow w3(LayoutObject::SizeHint(3,winWidth/3,1, 3,30,2));
	CLIWindow w4(LayoutObject::SizeHint(3,10,1, 3,30,2));
	CLIWindow w5(LayoutObject::SizeHint(3,10,1, 3,30,2));
	CLIWindow w6(LayoutObject::SizeHint(3,10,1, 3,30,2));
	CLIWindow w7(LayoutObject::SizeHint(1,winWidth,1, 2,2,1));

	vertical2.addObject(&w3);
	vertical2.addObject(&w4);
	vertical2.addObject(&w5);

	horizontal1. addObject(&w2);
	horizontal1. addObject(&vertical2);
	horizontal1. addObject(&w6);

	vertical1.addObject(&w1);
	vertical1.addObject(&horizontal1);
	vertical1.addObject(&w7);

	
	

	vertical1.setSize(winWidth, winHeight, border);

	fillWindow(w1, 'a');
	fillWindow(w2, 'b');
	fillWindow(w3, 'c');
	fillWindow(w4, 'd');
	fillWindow(w5, 'e');
	fillWindow(w6, 'f');
	fillWindow(w7, 'g');
	
	printBorder(vertical1, winHeight+5);



	return result;
}
