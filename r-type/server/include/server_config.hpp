/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-cyprien.diederichs
** File description:
** server_config.hpp
*/

#ifndef SERVER_CONFIG_HPP
#define SERVER_CONFIG_HPP

#include <iostream>
#include <thread>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <sys/socket.h>

constexpr int MAX_PLAYERS = 4;
constexpr int BUFFER_SIZE = 1024;
constexpr int PORT = 8080;

#endif // SERVER_CONFIG_HPP
