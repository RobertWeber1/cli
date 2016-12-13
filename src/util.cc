#include "util.h"
#include <iostream>

void checkEq(const std::string & a, const std::string & b, unsigned int & successful, unsigned int & count)
{
    count++;
    if(a == b)
    {
        successful++;
    }
    else
    {
        std::cout << "TEST[" << count << "] failed: string \"" << a << "\" should be equal to \"" << b << "\"" << std::endl;
    }
}