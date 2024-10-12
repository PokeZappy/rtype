#pragma once

const int BUFFER_SIZE = 1024;
const int PORT = 8080;
const int MAX_PLAYERS = 4;

#include "EngineInclude.hpp"

std::string assetFinder();

// Include Components

#include "MovementComponent.hpp"
#include "PlayerComponent.hpp"
#include "LifeComponent.hpp"
#include "CollisionComponent.hpp"
#include "ShootComponent.hpp"
#include "MonstreComponent.hpp"

// Include Events

#include "SendMessageEvent.hpp"

