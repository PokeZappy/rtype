/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-cyprien.diederichs
** File description:
** server.cpp
*/

#include "server_config.hpp"

potEngine::Server::Server() : current_players(0), network_system(4)
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

    std::cout << "Server started on port " << PORT << ". Waiting for clients...\n";
}

potEngine::Server::~Server()
{
    close(server_fd);
}

uint8_t potEngine::Server::assign_client_id()
{
    for (uint8_t id = 1; id <= MAX_PLAYERS; ++id) {
        auto it = std::find_if(clients.begin(), clients.end(), [id](const ClientInfo& client) {
            return client.client_id == id;
        });
        if (it == clients.end()) {
            return id;
        }
    }
    return 0;
}

void potEngine::Server::remove_client(uint8_t client_id)
{
    clients.erase(std::remove_if(clients.begin(), clients.end(), [client_id](const ClientInfo& client) {
        return client.client_id == client_id;
    }), clients.end());
}

void potEngine::Server::handle_action(uint8_t client_id, uint8_t action)
{
    auto entity_it = entities.find(client_id);
    if (entity_it != entities.end()) {
        auto player_entity = entity_it->second;
        auto network_component = player_entity->getComponent<NetworkComponent>();
        struct sockaddr_in client_addr = network_component->get()->_addr;

        switch (action) {
            case MOVE_UP:
                movement_system.moveUp(player_entity);
                network_system.send_message(server_fd, client_addr, client_id, MOVE_UP, {
                    static_cast<uint16_t>(player_entity->getComponent<PositionComponent>()->get()->_x),
                    static_cast<uint16_t>(player_entity->getComponent<PositionComponent>()->get()->_y)
                });
                break;

            case MOVE_DOWN:
                movement_system.moveDown(player_entity);
                network_system.send_message(server_fd, client_addr, client_id, MOVE_DOWN, {
                    static_cast<uint16_t>(player_entity->getComponent<PositionComponent>()->get()->_x),
                    static_cast<uint16_t>(player_entity->getComponent<PositionComponent>()->get()->_y)
                });
                break;

            case MOVE_LEFT:
                movement_system.moveLeft(player_entity);
                network_system.send_message(server_fd, client_addr, client_id, MOVE_LEFT, {
                    static_cast<uint16_t>(player_entity->getComponent<PositionComponent>()->get()->_x),
                    static_cast<uint16_t>(player_entity->getComponent<PositionComponent>()->get()->_y)
                });
                break;

            case MOVE_RIGHT:
                movement_system.moveRight(player_entity);
                network_system.send_message(server_fd, client_addr, client_id, MOVE_RIGHT, {
                    static_cast<uint16_t>(player_entity->getComponent<PositionComponent>()->get()->_x),
                    static_cast<uint16_t>(player_entity->getComponent<PositionComponent>()->get()->_y)
                });
                break;

            case DISCONNECT:
                current_players--;
                remove_client(client_id);
                entities.erase(client_id);
                network_system.send_message(server_fd, client_addr, client_id, DISCONNECT, std::vector<uint16_t>{});
                std::cout << "Client " << static_cast<int>(client_id) << " disconnected.\n";
                break;

            default:
                std::cout << "Unknown action from client " << static_cast<int>(client_id) << ".\n";
                break;
        }
    }
}

void potEngine::Server::handle_client_connection(uint8_t client_id, struct sockaddr_in client_addr)
{
    std::string player_name = "Player_" + std::to_string(static_cast<int>(client_id));
    create_player_entity(client_id, player_name, client_addr);
}


void potEngine::Server::create_player_entity(uint8_t client_id, const std::string& username, const sockaddr_in& client_addr)
{
    auto player_entity = std::make_shared<Entity>(client_id);
    player_entity->addComponent(std::make_shared<PlayerComponent>(username));
    player_entity->addComponent(std::make_shared<PositionComponent>(0.0f, 0.0f));
    player_entity->addComponent(std::make_shared<MovementComponent>(1.0f, 1.0f));
    player_entity->addComponent(std::make_shared<NetworkComponent>(4, client_addr));

    entities[client_id] = player_entity;
}

void potEngine::Server::start()
{
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    while (true) {
        auto [client_id, action, params] = network_system.recv_message(server_fd, client_addr, client_addr_len);
        if (action == CONNECTION) {
            uint8_t new_client_id = assign_client_id();
            if (new_client_id != 0) {
                clients.push_back({ new_client_id, client_addr });
                network_system.send_message(server_fd, client_addr, new_client_id, CONNECTION, {});
                handle_client_connection(new_client_id, client_addr);
                std::cout << "New client connected with ID " << static_cast<int>(new_client_id) << ".\n";
            } else {
                std::cout << "Server full. Cannot accept new clients.\n";
            }
        } else {
            handle_action(client_id, action);
        }
    }
}
