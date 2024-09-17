/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-cyprien.diederichs
** File description:
** event_handler.cpp
*/

#include "event_handler.hpp"

void handle_event(const std::string& client_input)
{
    if (client_input == "move") {
        std::cout << "Handling move event.\n";
    } else if (client_input == "shoot") {
        std::cout << "Handling shoot event.\n";
    } else {
        std::cout << "Unknown event: " << client_input << "\n";
    }
}
