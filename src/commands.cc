#include "commands.h"

const std::string VT100Commands::names[] = {
        "CMD0",
        "CMD1",
        "CMD2",
        "INVALID_CMD"
};


std::map<std::string, VT100Commands::CommandID> VT100Commands::init()
{
    std::map<std::string, VT100Commands::CommandID> result;
    result[ names[CMD0] ] = CMD0;
    result[ names[CMD1] ] = CMD1;
    result[ names[CMD2] ] = CMD2;
    return result;
}

VT100Commands::CommandID VT100Commands::operator[](const std::string& sequence)
{
    VT100Commands::CommandID result = VT100Commands::INVALID_CMD;
    std::map<std::string, VT100Commands::CommandID>::iterator findResult;

    findResult = commands.find(sequence);
    if(findResult != commands.end())
    {
        result = findResult->second;
    }

    return result;
}


std::ostream & operator<<(std::ostream& os, VT100Commands::CommandID id)
{
    os << "<" << VT100Commands::names[id] << ">";
    return os;
}
