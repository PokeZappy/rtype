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
const int SERVER_SOCKET = 1;
const int CLIENT_SOCKET = 1;

#include "AComponent.hpp"
#include "IComponent.hpp"
#include "MovementComponent.hpp"
#include "PositionComponent.hpp"
#include "NetworkComponent.hpp"
#include "PlayerComponent.hpp"
#include "SpriteComponent.hpp"
#include "WindowComponent.hpp"
#include "LifeComponent.hpp"
#include "CollisionComponent.hpp"
#include "ShootComponent.hpp"

#include "ASystem.hpp"
#include "ISystem.hpp"
#include "RenderSystem.hpp"
#include "InputSystem.hpp"
#include "RecvMessageSystem.hpp"
#include "AnimationSystem.hpp"
#include "ShipAnimationEvent.hpp"
#include "InputInfoEvent.hpp"
#include "MonstreComponent.hpp"

#include "AEventHandler.hpp"
#include "EventBus.hpp"
#include "IEvent.hpp"
#include "MemberHandler.hpp"

#include "ECSManager.hpp"
#include "AEntity.hpp"
#include "WindowEntity.hpp"

#include "EndEvent.hpp"
#include "MainLoopEvent.hpp"
#include "StartEvent.hpp"
#include "SendMessageEvent.hpp"
#include "SendMessageToAllEvent.hpp"
#include "SendMessageToAllExeptEvent.hpp"
#include "DisconnectionEvent.hpp"
#include "ConnectionEvent.hpp"
#include "MoveEvent.hpp"
#include "CollisionEvent.hpp"
#include "InputToServerEvent.hpp"

#endif // GAME_CONFIG_HPP

