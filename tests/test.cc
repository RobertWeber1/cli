#include "version.h"
#include "commands.h"
#include <iostream>
#include <sstream>


//VT100Commands cmds;

int main()
{
    std::stringstream version;
    version << PROJECT_NAME << "("<< SHORT_NAME <<") V"
            << VERSION_MAJOR << "."
            << VERSION_MINOR << "."
            << VERSION_PATCH;
    std::cout << "------- "<< version.str() <<" -------" << std::endl;

    VT100Commands cmds;
    VT100Commands::CommandID id;

    std::string testCMD = "CMD2";
    id = cmds[testCMD];


    if(id == VT100Commands::INVALID_CMD)
    {
        std::cout << testCMD << " = " << cmds[testCMD] << std::endl;
    }
    else
    {
        std::cout << testCMD << " = " << (int)cmds[testCMD] << std::endl;
    }

    std::cout << VT100Commands::CMD0 << std::endl;

    std::cout << "--------------------- END ---------------------" << std::endl;

    return 0;
}
