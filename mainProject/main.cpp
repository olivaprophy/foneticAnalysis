#include <limits>
#include <functional>
#include <iostream>
#include "userCmds.hpp"
#include "internalFuncs.hpp"

int main()
{
    using storage_t = std::map< std::string, std::vector< std::string > >;
    std::map< std::string, storage_t > depot;
    std::string defaultSt = "";
    std::map< std::string, std::function < void(std::istream&, std::ostream&, std::map< std::string, storage_t >&) > > userCmds;
    {
        using namespace std::placeholders;
        userCmds["help"] = std::bind(myFuncs::cmdHelp, _1, _2);
        userCmds["create"] = std::bind(myFuncs::cmdCreate, _1, _2, _3, "");
        userCmds["delete"] = myFuncs::cmdDelete;
        userCmds["list"] = std::bind(myFuncs::cmdList, _2, _3);
        userCmds["show"] = myFuncs::cmdShow;
        userCmds["rename"] = myFuncs::cmdRename;
        userCmds["choose"] = std::bind(myFuncs::cmdCreate, _1, _2, _3, defaultSt);
        userCmds["save"] = myFuncs::cmdSave;

        userCmds["print"] = std::bind(myFuncs::cmdPrint, _1, _2, _3, defaultSt);
        userCmds["fono"] = std::bind(myFuncs::cmdFono, _1, _2);
        userCmds["makeSent"] = std::bind(myFuncs::cmdMakeSent, _1, _2, _3, defaultSt);
    }

    std::string userCmd = "";
    while (std::cin >> userCmd)
    {
        try
        {
            userCmds.at(userCmd)(std::cin, std::cout, depot);
        }
        catch (const std::logic_error&)
        {
            myFuncs::outError(std::cout, "<INVALID COMMAND>");
            std::cin.clear();
            std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
        }
    }
}
