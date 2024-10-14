/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-cyprien.diederichs
** File description:
** Parameters.cpp
*/

#include "Parameters.hpp"

/*!
* @brief Construct a new Parameters object.
*
* This constructor initializes the Parameters object with default values for IP and port.
*
* @param argc The number of arguments.
* @param argv The array of arguments.
* @throws std::runtime_error If an invalid port number is provided.
*/
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
/*!
* @brief Destroy the Parameters object.
*/
Parameters::~Parameters()
{
}

/*!
* @brief Get the IP address.
*
* @return std::string The IP address.
*/
std::string Parameters::getIp() const
{
    return _ip;
}

/*!
* @brief Get the port number.
*
* @return int The port number.
*/
int Parameters::getPort() const
{
    return _port;
}
