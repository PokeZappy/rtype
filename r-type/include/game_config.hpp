/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** game_config.hpp
*/

#ifndef GAME_CONFIG_HPP
#define GAME_CONFIG_HPP

const int BUFFER_SIZE = 1024;
const int PORT = 8080;
const int MAX_PLAYERS = 4;

#include "AComponent.hpp"
#include "IComponent.hpp"
#include "MovementComponent.hpp"
#include "PositionComponent.hpp"
#include "NetworkComponent.hpp"

#include "ASystem.hpp"
#include "ISystem.hpp"
#include "MovementSystem.hpp"
#include "NetworkSystem.hpp"

#include "ECSManager.hpp"
#include "Entity.hpp"
#include "Event.hpp"

#endif // GAME_CONFIG_HPP
