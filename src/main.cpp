#include "Server.hpp"

#include <iostream>
#include <exception>

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    try
    {
        Server irc;

        irc.run();
    }
    catch (std::exception &e)
    {
        std::cerr << e.what(); 

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
