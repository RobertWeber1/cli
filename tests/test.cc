#include <iostream>
#include <sstream>
#include "version.h"

int main()
{
    std::stringstream version;
    version << PROJECT_NAME << "("<< SHORT_NAME <<") V"
            << VERSION_MAJOR << "."
            << VERSION_MINOR << "."
            << VERSION_PATCH;
    std::cout << "------- "<< version.str() <<" -------" << std::endl;



    std::cout << "--------------------- END ---------------------" << std::endl;

    return 0;
}
