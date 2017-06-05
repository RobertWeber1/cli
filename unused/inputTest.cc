#include "inputmultiplexer.h"
#include <iostream>
#include <iomanip>
#include <unistd.h>

int main(int argc, char *argv[])
{

	std::cout << "---------------------- start of input-test ----------------------" << std::endl;

	
	LockupMap lookupMap;

	for(unsigned char i = 0; i < 130; i++)
	{
		std::cout << (int)i << ": " << lookupMap.lookup(i) << std::endl;
	}


	std::cout << "----------------------- end of input-test -----------------------" << std::endl;

	{
		InputMultiplexer im(std::cin);


		std::cout << "\033[0c" << std::endl;

		std::string seq;

		std::cin >> seq;

		std::cout << std::endl;

		for(int i=0; i<seq.size(); i++)
		{
			std::cout << std::setw(2) << std::setfill('0') << std::hex << (int)seq.at(i) << " ";
		}

		std::cout << std::endl;

		while(true)
		{
			usleep(10000);
		}
	}
	return 0;
}

