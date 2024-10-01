/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-cyprien.diederichs
** File description:
** server.cpp
*/

#include "server_config.hpp"

RType::Server::Server() : current_players(0), ecs_manager(std::make_shared<polEngine::ECSManager>())
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

    server_entity = std::make_shared<polEngine::Entity>(0);
    auto network_component = std::make_shared<polEngine::NetworkComponent>(server_fd, server_addr);
    server_entity->addComponent(network_component);

    ecs_manager->addEntity(server_entity);
}

RType::Server::~Server()
{
    close(server_fd);
}

uint8_t RType::Server::assign_client_id()
{
    for (uint8_t id = 1; id <= MAX_PLAYERS; ++id) {
        if (!ecs_manager->hasEntity(id)) {
            return id;
        }
    }
    return 0;
}

void RType::Server::remove_client(uint8_t client_id)
{
    ecs_manager->removeEntity(client_id);
}

void RType::Server::handle_action(uint8_t client_id, uint8_t action)
{
    auto player_entity = ecs_manager->getEntity(client_id);
    if (player_entity) {
        auto network_component = player_entity->getComponent<polEngine::NetworkComponent>();
        auto movement_system = player_entity->getComponent<polEngine::MovementComponent>();
        struct sockaddr_in client_addr = network_component->addr;

        switch (action) {
            case polEngine::MOVE_UP:
                movement_system.moveUp(player_entity);
                network_component->send_message(client_addr, client_id, polEngine::MOVE_UP, {
                    static_cast<uint16_t>(player_entity->getComponent<polEngine::PositionComponent>()->get()->_x),
                    static_cast<uint16_t>(player_entity->getComponent<polEngine::PositionComponent>()->get()->_y)
                });
                break;

            case polEngine::MOVE_DOWN:
                movement_system.moveDown(player_entity);
                network_component->send_message(client_addr, client_id, polEngine::MOVE_DOWN, {
                    static_cast<uint16_t>(player_entity->getComponent<polEngine::PositionComponent>()->get()->_x),
                    static_cast<uint16_t>(player_entity->getComponent<polEngine::PositionComponent>()->get()->_y)
                });
                break;

            case polEngine::MOVE_LEFT:
                movement_system.moveLeft(player_entity);
                network_component->send_message(client_addr, client_id, polEngine::MOVE_LEFT, {
                    static_cast<uint16_t>(player_entity->getComponent<polEngine::PositionComponent>()->get()->_x),
                    static_cast<uint16_t>(player_entity->getComponent<polEngine::PositionComponent>()->get()->_y)
                });
                break;

            case polEngine::MOVE_RIGHT:
                movement_system.moveRight(player_entity);
                network_component->send_message(client_addr, client_id, polEngine::MOVE_RIGHT, {
                    static_cast<uint16_t>(player_entity->getComponent<polEngine::PositionComponent>()->get()->_x),
                    static_cast<uint16_t>(player_entity->getComponent<polEngine::PositionComponent>()->get()->_y)
                });
                break;

            case polEngine::DISCONNECT:
                current_players--;
                remove_client(client_id);
                network_component->send_message(client_addr, client_id, polEngine::DISCONNECT, std::vector<uint16_t>{});
                std::cout << "Client " << static_cast<int>(client_id) << " disconnected.\n";
                break;

            default:
                std::cout << "Unknown action from client " << static_cast<int>(client_id) << ".\n";
                break;
        }
    }
}

void RType::Server::handle_client_connection(uint8_t client_id, struct sockaddr_in client_addr, std::vector<uint16_t> params)
{
    std::string player_name;

    if (params.empty()) {
        player_name = "Player_" + std::to_string(static_cast<int>(client_id));
    } else {
        player_name.assign(params.begin(), params.end());
    }
    create_player_entity(client_id, player_name, client_addr);
}

void RType::Server::create_player_entity(uint8_t client_id, const std::string& username, const sockaddr_in& client_addr)
{
    auto player_entity = std::make_shared<polEngine::Entity>(client_id);
    player_entity->addComponent(std::make_shared<polEngine::PlayerComponent>(username));
    player_entity->addComponent(std::make_shared<polEngine::PositionComponent>(0.0f, 0.0f));
    player_entity->addComponent(std::make_shared<polEngine::MovementComponent>(1.0f));
    player_entity->addComponent(std::make_shared<polEngine::NetworkComponent>(1, client_addr));

    ecs_manager->addEntity(player_entity);
    std::cout << "[SERVER] New Player Entity created: {id}-[" << std::to_string(static_cast<int>(client_id)) << "], {username}-[" << username << "]" << std::endl;
}

void RType::Server::start()
{
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    while (true) {
        auto [client_id, action, params] = server_entity->getComponent<polEngine::NetworkComponent>()->recv_message(client_addr, client_addr_len);
        if (action == CONNECTION) {
            uint8_t new_client_id = assign_client_id();
            if (new_client_id != 0) {
                std::cout << "[SERVER] New client connected with ID " << static_cast<int>(new_client_id) << ".\n";
                server_entity->getComponent<polEngine::NetworkComponent>()->send_message(client_addr, new_client_id, polEngine::CONNECTION, {});
                handle_client_connection(new_client_id, client_addr, params);
                current_players++;
            } else {
                std::cout << "[SERVER] Server full. Cannot accept new clients.\n";
            }
        } else {
            handle_action(client_id, action);
        }
        ecs_manager->update(0.016f);
    }
}
