/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-cyprien.diederichs
** File description:
** main.cpp
*/

#include "client_config.hpp"
#include "Parameters.hpp"

int main(int argc, char **argv)
{
    std::string asset_path = assetFinder();
    if (asset_path.empty()) {
        std::cerr << "Can't find the r-type asset folder" << std::endl;
        return 84;
    }

    Parameters parameters(argc, argv);
    RType::Client client(parameters.getIp(), parameters.getPort());
    // title_screen(asset_path);
    client.start();
    return 0;
}
