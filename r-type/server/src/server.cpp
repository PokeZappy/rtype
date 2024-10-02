/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-cyprien.diederichs
** File description:
** server.cpp
*/

#include "server_config.hpp"

RType::Server::Server() : current_players(0), ecs_manager(std::make_shared<potEngine::ECSManager>())
{
    if ((server_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_fd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
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

void RType::Server::handle_client_disconnection(uint8_t entity_id)
{
    std::string player_name = ecs_manager.get()->getEntity(entity_id).get()->getComponent<potEngine::PlayerComponent>()->get()->username;

    std::cout << "[SERVER] Player disconnected: {id}-[" << std::to_string(static_cast<int>(entity_id)) << "], {username}-[" << player_name << "]" << std::endl;
    ecs_manager->removeEntity(entity_id);
    send_message_to_all(entity_id, potEngine::DISCONNECT, std::vector<uint16_t>{}, ecs_manager.get()->getEntities());
    current_players--;
}

void RType::Server::handle_client_connection(struct sockaddr_in client_addr, std::vector<uint16_t> params)
{
    auto player_entity = ecs_manager->createEntity();
    uint8_t player_id = player_entity->getID();
    std::string player_name;

    if (params.empty()) {
        player_name = "Player_" + std::to_string(static_cast<int>(player_id));
    } else {
        player_name.assign(params.begin(), params.end());
    }

    std::shared_ptr<potEngine::PlayerComponent> playerComponent = std::make_shared<potEngine::PlayerComponent>(player_name);
    std::shared_ptr<potEngine::PositionComponent> positionComponent = std::make_shared<potEngine::PositionComponent>(0.0f, 0.0f);
    std::shared_ptr<potEngine::MovementComponent> movementComponent = std::make_shared<potEngine::MovementComponent>(1.0f);
    std::shared_ptr<potEngine::NetworkComponent> networkComponent = std::make_shared<potEngine::NetworkComponent>(client_addr);

    ecs_manager->addComponent(player_entity, playerComponent);
    ecs_manager->addComponent(player_entity, positionComponent);
    ecs_manager->addComponent(player_entity, movementComponent);
    ecs_manager->addComponent(player_entity, networkComponent);


    std::cout << "[SERVER] Player connected: {id}-[" << std::to_string(static_cast<int>(player_id)) << "], {username}-[" << player_name << "]" << std::endl;
    send_message(client_addr, player_id, potEngine::CONNECTION, {});
    current_players++;
}

void RType::Server::handle_action(uint8_t entity_id, struct sockaddr_in client_addr, potEngine::EventType action, std::vector<uint16_t> params)
{
    // if (action == potEngine::CONNECTION) {
    //     potEngine::ConnectionInfoEvent connectionInfo;
    //     connectionInfo.client_addr = client_addr;
    //     connectionInfo.params = params;
    //     connectionInfo.ecs_manager = ecs_manager;

    //     potEngine::eventBus. .publish(connectionInfo);
    // }

    if (action == potEngine::CONNECTION) {
        if (current_players < MAX_PLAYERS) {
            handle_client_connection(client_addr, params);
        } else {
            std::cout << "[SERVER] Server full. Cannot accept new clients.\n";
            // faut encore déco le client
        }
    }

    if (action == potEngine::DISCONNECT) {
        handle_client_disconnection(entity_id);
    }
}

void RType::Server::start()
{
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    const float fixedDeltaTime = 1.0f / 60.0f;
    auto lastUpdateTime = std::chrono::high_resolution_clock::now();

    int flags = fcntl(SERVER_SOCKET, F_GETFL, 0);
    fcntl(SERVER_SOCKET, F_SETFL, flags | O_NONBLOCK);

    while (true) {
        auto [entity_id, event_type, params] = recv_message(client_addr, client_addr_len);

        if (entity_id != 0 || event_type != potEngine::EventType::UNKNOW) {
            handle_action(entity_id, client_addr, event_type, params);
        }

        auto now = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> elapsedTime = now - lastUpdateTime;

        if (elapsedTime.count() >= fixedDeltaTime) {
            ecs_manager->update(fixedDeltaTime);
            lastUpdateTime = now;
        }
    }
}

