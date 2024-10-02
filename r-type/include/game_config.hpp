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
#include "PlayerComponent.hpp"
#include "RenderComponent.hpp"
#include "WindowComponent.hpp"

#include "ASystem.hpp"
#include "ISystem.hpp"
#include "MovementSystem.hpp"
#include "NetworkSystem.hpp"
#include "RenderSystem.hpp"

#include "AEventHandler.hpp"
#include "EventBus.hpp"
#include "IEvent.hpp"
#include "MemberHandler.hpp"

#include "ECSManager.hpp"
#include "AEntity.hpp"
#include "WindowEntity.hpp"

#include "EndEvent.hpp"
#include "EventRender.hpp"
#include "MainLoopEvent.hpp"
#include "StartEvent.hpp"

#endif // GAME_CONFIG_HPP
