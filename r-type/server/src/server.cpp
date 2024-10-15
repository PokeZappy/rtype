/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-cyprien.diederichs
** File description:
** server.cpp
*/

#include "server_config.hpp"

void RType::Server::init(int port) {
    if ((server_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    _addr_len = sizeof(_addr);
    memset(&_addr, 0, _addr_len);
    _addr.sin_family = AF_INET;
    _addr.sin_addr.s_addr = INADDR_ANY;
    _addr.sin_port = htons(port);
    if (bind(server_fd, (const struct sockaddr *)&_addr, _addr_len) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    std::cout << "[SERVER] started on port " << port << ". Waiting for clients...\n";
}

RType::Server::Server() : current_players(0)
{
    // INIT_WINSOCK();
    init(PORT);
}

RType::Server::Server(int port) : current_players(0)
{
    init(port);
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
    auto MoveServerEvent = std::make_shared<potEngine::MoveServerEvent>();
    auto collisionEvent = std::make_shared<potEngine::CollisionEvent>();
    auto startStageEvent = std::make_shared<potEngine::StartStageEvent>();
    auto stageEvent = std::make_shared<potEngine::StageEvent>(server_fd);
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

    std::thread recvThread([this]() {
        while (true) {
            handle_message();
        }
    });

    potEngine::engine.registerSystem<potEngine::MoveServerEntitySystem>();

    potEngine::engine.timer.setTps(20);
    auto startEvent = std::make_shared<potEngine::StartEvent>();
    potEngine::engine.publishEvent(startEvent);
    potEngine::engine.update();
    recvThread.join();
}
