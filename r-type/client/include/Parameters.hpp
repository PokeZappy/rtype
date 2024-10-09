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