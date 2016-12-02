#include "data.h"

int main(int argc, char * argv[])
{
	Data dat1, dat2;

	dat1 << "test1" << std::endl;

	dat2 << "test2" << std::endl;

	dat1.processData();
	dat2.processData();

	return 0;
}