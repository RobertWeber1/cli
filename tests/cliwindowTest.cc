#include "cliwindow.h"
#include <iostream>
#include <iomanip>

void printWindow(const CLIWindow& win)
{
	std::cout << "+" << std::setw(win.Width()) << std::setfill('-') << "-" << "+" << std::endl;

	for(int i = 0; i< win.Height(); i++)
	{
		std::cout << "|";
		win.toStream(std::cout, i);
		std::cout << "|" << std::endl;
	}

	std::cout << "+" << std::setw(win.Width()) << std::setfill('-') << "-" << "+" << std::endl;
}

void testGraphicsMode()
{
	char start = 0x5f;
	char end = 0x7e;

	std::cout << "\033(0";

	for(char i = start; i<=end; i++)
	{
		std::cout << i << std::endl;
	}



	std::cout << "\033(B";
	for(char i = start; i<=end; i++)
	{
		std::cout << i << std::endl;
	}
}


int main(int argc, char* argv[])
{
    int result = 0;

    CLIWindow win(LayoutObject::Size(LayoutObject::SizeConstraint(1,25,2)), 7);
	win.resize(3, 19);
    win.appendLine("");
    win.appendLine("1_1_1_1_1.1_1_1_1_1.");
    win.appendLine("");
    win.appendLine("2_2_2_2_2.2_2_2_2_2.");
    win.appendLine("");
    win.appendLine("3_3_3_3_3.3_3_3_3_3.");
    win.appendLine("");

    std::cout << "TEST 1:" << std::endl;
    win.printLines();
    std::cout << std::endl;

    std::cout << "lockup TEST 1:" << std::endl;
    win.printLookup();
    std::cout << std::endl;

	printWindow(win);



    win.removeLine(0);
    win.removeLine(1);
    win.removeLine(2);

    std::cout << "remove 3 Lines:" << std::endl;
    win.printLookup();
    std::cout << std::endl;

	printWindow(win);


    win.appendLine("4_4_4_4_4.4_4_4_4_4.");
    std::cout << "TEST 2:" << std::endl;
    win.printLines();
    std::cout << std::endl;


	printWindow(win);

    std::cout << "lockup TEST 2:" << std::endl;
    win.printLookup();
    std::cout << std::endl;

    win.appendLine("5_5_5_5_5.5_5_5_5_5.");
    std::cout << "TEST 3:" << std::endl;
    win.printLines();
    std::cout << std::endl;

	printWindow(win);

    std::cout << "lockup TEST 3:" << std::endl;
    win.printLookup();
    std::cout << std::endl;

    std::cout << "Remove line with index \"1\"" << std::endl;
    win.removeLine(1);
    win.printLines();
    std::cout << std::endl;
    win.printLookup();
    std::cout << std::endl;

	printWindow(win);

    std::cout << "remove not existing lines:" << std::endl;
    win.removeLine(6);
    win.removeLine(7);

    win.printLookup();
    std::cout << std::endl;

	printWindow(win);

	std::cout << "insert Line at index 3" << std::endl;
	win.insertLine(3, "1_i_i_i_i.I_I_I_I_I.");
	std::cout << std::endl;

	win.printLines();
    std::cout << std::endl;
	win.printLookup();
	std::cout << std::endl;

	printWindow(win);

	std::cout << "insert Line at index 3" << std::endl;
	win.insertLine(0, "0_b_b_b_b.B_B_B_B_B.");
	std::cout << std::endl;

	win.printLines();
    std::cout << std::endl;
	win.printLookup();
	std::cout << std::endl;

	printWindow(win);

	std::cout << "insert Line at index 3" << std::endl;
	win.insertLine(3, "2_i_i_i_i.I_I_I_I_I.");
	std::cout << std::endl;

	printWindow(win);

	win.printLines();
    std::cout << std::endl;
	win.printLookup();
	std::cout << std::endl;

	std::cout << "insert Line at index 3" << std::endl;
	win.insertLine(3, "3_i_i_i_i.I_I_I_I_I.");
	std::cout << std::endl;

	printWindow(win);

	win.printLines();
    std::cout << std::endl;
	win.printLookup();
	std::cout << std::endl;

	std::cout << "insert Line at index 3" << std::endl;
	win.insertLine(0, "4_i_i_i_i.I_I_I_I_I.");
	std::cout << std::endl;

	win.printLines();
    std::cout << std::endl;
	win.printLookup();
	std::cout << std::endl;

	printWindow(win);

	std::cout << "insert Line at index 3" << std::endl;
	win.replaceLine(6, "5_r_r_r_r.R_R_R_R_R.");
	std::cout << std::endl;

	win.printLines();
    std::cout << std::endl;
	win.printLookup();
	std::cout << std::endl;

	printWindow(win);

	std::cout << "----------ToTop---------" << std::endl;
	win.scrollToTop();
	printWindow(win);

	std::cout << "scroll down 1 line" << std::endl;
	win.scrollDown(1);
	printWindow(win);

	std::cout << "scroll down 2 line" << std::endl;
	win.scrollDown(2);
	printWindow(win);

	std::cout << "scroll down 3 line" << std::endl;
	win.scrollDown(3);
	printWindow(win);

	std::cout << "scroll down 4 line" << std::endl;
	win.scrollDown(4);
	printWindow(win);

	std::cout << "resize to 5,5" << std::endl;
	win.resize(5, 5);
	printWindow(win);


	std::cout << "resize to 30,30" << std::endl;
	win.resize(15, 30);
	printWindow(win);
//testGraphicsMode();
}
