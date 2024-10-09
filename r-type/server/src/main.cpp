/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-cyprien.diederichs
** File description:
** main.cpp
*/

#include "server_config.hpp"

int main(int argc, char **argv)
{
    if (argc == 1) {
        RType::Server server;
        server.start();
    } else if (std::stoi(argv[1])) {
        RType::Server server(std::stoi(argv[1]));
        server.start();
    } else {
        std::cerr << "Usage: ./rtype_server [port]" << std::endl;
        std::cerr << "Usage: ./rtype_server [port]" << std::endl;
        return 1;
    }
    return 0;
}
