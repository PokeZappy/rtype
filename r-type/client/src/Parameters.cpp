/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-cyprien.diederichs
** File description:
** Parameters.cpp
*/

#include "Parameters.hpp"

Parameters::Parameters(int argc, char **argv) : _ip("127.0.0.1"), _port(8080)
{
    for (int i = 1; i < argc; i++) {
        if (std::string(argv[i]) == "-ip" && i + 1 < argc) {
            _ip = argv[++i];
        } else if (std::string(argv[i]) == "-p" && i + 1 < argc) {
            try {
                _port = std::stoi(argv[++i]);
            } catch (const std::invalid_argument&) {
                throw std::runtime_error("Invalid port number.");
            }
        } else {
            std::cerr << "Usage: " << argv[0] << " -ip [ip] -p [port]" << std::endl;
            exit(84);
        }
    }
}

Parameters::~Parameters()
{
}

std::string Parameters::getIp() const
{
    return _ip;
}

int Parameters::getPort() const
{
    return _port;
}
