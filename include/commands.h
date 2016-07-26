#include <map>
#include <string>
#include <iostream>


class VT100Commands
{
public:
    typedef enum CommandID{
        CMD0 = 0,
        CMD1,
        CMD2,
        INVALID_CMD
    }CommandID;

private:
    std::map<std::string, CommandID> commands;
    std::map<std::string, CommandID> init();

public:
    static const std::string names[];

    VT100Commands():commands(init()){};
    CommandID operator[](const std::string& sequence);

    friend std::ostream & operator<<(std::ostream& os, CommandID id);


};

std::ostream & operator<<(std::ostream& os, VT100Commands::CommandID id);
