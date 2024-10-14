/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-cyprien.diederichs
** File description:
** server.cpp
*/

#include "server_config.hpp"

RType::Server::Server() : current_players(0)
{
    INIT_WINSOCK();
    if ((server_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr_len = sizeof(server_addr);
    memset(&server_addr, 0, server_addr_len);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);


    if (bind(server_fd, (const struct sockaddr *)&server_addr, server_addr_len) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    std::cout << "[SERVER] started on port " << PORT << ". Waiting for clients...\n";
}

RType::Server::~Server()
{
    close(server_fd);
}

void RType::Server::init_subscribe()
{
    auto connectionEvent = std::make_shared<potEngine::ConnectionEvent>();
    auto disconnectionEvent = std::make_shared<potEngine::DisconnectionEvent>();
    auto sendMessageToAllEvent = std::make_shared<potEngine::SendMessageToAllEvent>();
    auto sendAllDataEvent = std::make_shared<potEngine::SendAllDataEvent>();
    auto sendMessageToAllExeptEvent = std::make_shared<potEngine::SendMessageToAllExeptEvent>();
    auto sendMessageEvent = std::make_shared<potEngine::SendMessageEvent>();
    auto moveEvent = std::make_shared<potEngine::MoveEvent>();
    auto collisionEvent = std::make_shared<potEngine::CollisionEvent>();
    auto startStageEvent = std::make_shared<potEngine::StartStageEvent>();
    auto stageEvent = std::make_shared<potEngine::StageEvent>();
    auto entityCreateEvent = std::make_shared<potEngine::EntityCreateEvent>();
}

void RType::Server::setNonBlockingInput()
{
    SET_NONBLOCKING(server_fd)
}

void RType::Server::start()
{
    init_subscribe();
    setNonBlockingInput();

    potEngine::engine.registerSystem<potEngine::RecvMessageServerSystem>(server_fd, server_addr, server_addr_len);
    potEngine::engine.registerSystem<potEngine::ShootEntitySystem>();

    potEngine::engine.timer.setTps(145);
    auto startEvent = std::make_shared<potEngine::StartEvent>();
    potEngine::engine.publishEvent(startEvent);
    potEngine::engine.update();
}
