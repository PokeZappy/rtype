/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-cyprien.diederichs
** File description:
** Parameters.hpp
*/

#ifndef PARAMETERS_HPP
    #define PARAMETERS_HPP

    #include <string>
    #include <iostream>

/*!
* @brief Class to handle command line parameters.
*
* This class is responsible for parsing and storing the IP address and port number from the command line arguments.
*/
class Parameters {
    public :
        Parameters(int argc, char **argv);
        ~Parameters();

        std::string getIp() const;
        int getPort() const;

    private:
        std::string _ip;
        int _port;
};

#endif // PARAMETERS_HPP