/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-cyprien.diederichs
** File description:
** server.cpp
*/

#include "server_config.hpp"

RType::Server::Server() : current_players(0)
{
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

void RType::Server::handle_action(uint8_t entity_id, struct sockaddr_in client_addr, potEngine::EventType action, std::vector<uint16_t> params)
{
    if (action == potEngine::CONNECTION && MAX_PLAYERS > current_players) {
        auto connectionInfo = std::make_shared<potEngine::ConnectionInfoEvent>(
            MAX_PLAYERS, server_fd, client_addr, params
        );
        potEngine::eventBus.publish(connectionInfo);
        current_players++;
    }

    if (action == potEngine::DISCONNECT) {
        auto disconnectInfo = std::make_shared<potEngine::DisconnectionInfoEvent>(MAX_PLAYERS, server_fd, entity_id, params);
        potEngine::eventBus.publish(disconnectInfo);
        current_players--;
    }

    if (action == potEngine::MOVE_UP || action == potEngine::MOVE_DOWN || action == potEngine::MOVE_RIGHT || action == potEngine::MOVE_LEFT) {
        auto moveInfo = std::make_shared<potEngine::MoveInfoEvent>(MAX_PLAYERS, server_fd, action, entity_id, params);
        potEngine::eventBus.publish(moveInfo);
    }

    if (action == potEngine::START_STAGE) {
        for (auto entity : potEngine::ecsManager.getEntities()) {
            if (entity->hasComponent<potEngine::StageComponent>()) {
                return;
            }
        }
        auto startStage = std::make_shared<potEngine::StratStageInfoEvent>(MAX_PLAYERS, server_fd, entity_id, params);
        potEngine::eventBus.publish(startStage);
    }
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
    int flags = fcntl(server_fd, F_GETFL, 0);
    fcntl(server_fd, F_SETFL, flags | O_NONBLOCK);
}

void RType::Server::start()
{
    init_subscribe();
    setNonBlockingInput();

    potEngine::ecsManager.registerSystem<potEngine::RecvMessageServerSystem>(server_fd, server_addr, server_addr_len);
    potEngine::ecsManager.registerSystem<potEngine::ShootEntitySystem>(server_fd, 0.001f);

    auto startEvent = std::make_shared<potEngine::StartEvent>();

    potEngine::eventBus.publish(startEvent);
    potEngine::ecsManager.update(0.016);
}
