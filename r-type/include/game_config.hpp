/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** game_config.hpp
*/

#ifndef GAME_CONFIG_HPP
#define GAME_CONFIG_HPP

#define CONNECTION 0x01
#define DISCONNECT 0x02
#define MOVE_UP 0x03
#define MOVE_DOWN 0x04
#define MOVE_LEFT 0x05
#define MOVE_RIGHT 0x06

constexpr int BUFFER_SIZE = 1024;
constexpr int PORT = 8080;
constexpr int MAX_PLAYERS = 4;
constexpr int MAX_ACTIONS = 5;

#endif // GAME_CONFIG_HPP
