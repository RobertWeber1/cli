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

    std::string testCMD = "\033[2J";
    id = cmds[testCMD];


    if(id == VT100Commands::INVALID_CMD)
    {
        std::cout << testCMD << " = " << cmds[testCMD] << std::endl;
    }
    else
    {
        std::cout << testCMD << " = " << (int)cmds[testCMD] << std::endl;
    }

    std::cout << VT100Commands::ERASE_SCREEN << std::endl;


    StreamCMD scmds;
    StreamCMD::CommandID sid;

    std::string inputCMD = "\033<";
    sid = scmds[inputCMD];

    std::cout << "shold be LEFT-CMD: " << scmds.toString(sid) << "(" << StreamCMD::UPDATE << ")" << std::endl;


    std::cout << "--------------------- END ---------------------" << std::endl;

    return 0;
}
