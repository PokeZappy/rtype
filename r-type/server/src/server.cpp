/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-cyprien.diederichs
** File description:
** main.cpp
*/

#include "server_config.hpp"

potEngine::Server::Server() : current_players(0)
{
    if ((server_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_fd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
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
        std::shared_ptr<Entity> player_entity = entity_it->second;
        sockaddr_in client_addr;
        bool client_found = false;

        for (const auto& client : clients) {
            if (client.client_id == client_id) {
                client_addr = client.client_addr;
                client_found = true;
                break;
            }
        }
        if (!client_found) {
            std::cerr << "Client address not found for client ID " << static_cast<int>(client_id) << ".\n";
            return;
        }

        switch (action) {
            case MOVE_UP:
                std::cout << "Client " << static_cast<int>(client_id) << " moves up.\n";
                this->movement_system.moveUp(player_entity);
                std::cout << "Sending position (" << player_entity->getComponent<PositionComponent>()->get()->x << ", " << player_entity->getComponent<PositionComponent>()->get()->y << ") to client " << static_cast<int>(client_id) << ".\n";
                this->send_system.send_message(
                    server_fd,
                    client_addr,
                    client_id,
                    MOVE_UP,
                    {static_cast<uint16_t>(player_entity->getComponent<PositionComponent>()->get()->x),
                    static_cast<uint16_t>(player_entity->getComponent<PositionComponent>()->get()->y)}
                );
                break;
            case MOVE_DOWN:
                std::cout << "Client " << static_cast<int>(client_id) << " moves down.\n";
                this->movement_system.moveDown(player_entity);
                std::cout << "Sending position (" << player_entity->getComponent<PositionComponent>()->get()->x << ", " << player_entity->getComponent<PositionComponent>()->get()->y << ") to client " << static_cast<int>(client_id) << ".\n";
                this->send_system.send_message(
                    server_fd,
                    client_addr,
                    client_id,
                    MOVE_DOWN,
                    {static_cast<uint16_t>(player_entity->getComponent<PositionComponent>()->get()->x),
                    static_cast<uint16_t>(player_entity->getComponent<PositionComponent>()->get()->y)}
                );
                break;
            case MOVE_LEFT:
                std::cout << "Client " << static_cast<int>(client_id) << " moves left.\n";
                this->movement_system.moveLeft(player_entity);
                std::cout << "Sending position (" << player_entity->getComponent<PositionComponent>()->get()->x << ", " << player_entity->getComponent<PositionComponent>()->get()->y << ") to client " << static_cast<int>(client_id) << ".\n";
                this->send_system.send_message(
                    server_fd,
                    client_addr,
                    client_id,
                    MOVE_LEFT,
                    {static_cast<uint16_t>(player_entity->getComponent<PositionComponent>()->get()->x),
                    static_cast<uint16_t>(player_entity->getComponent<PositionComponent>()->get()->y)}
                );
                break;
            case MOVE_RIGHT:
                std::cout << "Client " << static_cast<int>(client_id) << " moves right.\n";
                this->movement_system.moveRight(player_entity);
                std::cout << "Sending position (" << player_entity->getComponent<PositionComponent>()->get()->x << ", " << player_entity->getComponent<PositionComponent>()->get()->y << ") to client " << static_cast<int>(client_id) << ".\n";
                this->send_system.send_message(
                    server_fd,
                    client_addr,
                    client_id,
                    MOVE_DOWN,
                    {static_cast<uint16_t>(player_entity->getComponent<PositionComponent>()->get()->x),
                    static_cast<uint16_t>(player_entity->getComponent<PositionComponent>()->get()->y)}
                );
                break;
            case DISCONNECT:
                std::cout << "Client " << static_cast<int>(client_id) << " is disconnecting.\n";
                remove_client(client_id);
                current_players--;
                this->send_system.send_message(server_fd, client_addr, client_id, DISCONNECT, std::vector<uint16_t>{});
                return;
            default:
                std::cout << "Unknown action.\n";
                return;
        }
    } else {
        std::cout << "No entity found for client " << static_cast<int>(client_id) << ".\n";
    }
}

void potEngine::Server::handle_client_connection(int client_id)
{
    std::shared_ptr<Entity> player = std::make_shared<Entity>(client_id);
    std::shared_ptr<potEngine::PositionComponent> PositionComponentPtr = std::make_shared<PositionComponent>(0, 0);
    std::shared_ptr<potEngine::MovementComponent> MovementComponentPtr = std::make_shared<MovementComponent>(0, 0);

    player->addComponent(PositionComponentPtr);
    player->addComponent(MovementComponentPtr);
    entities[client_id] = player;
    std::cout << "Client " << client_id << " connected and Player entity created.\n";
}

void potEngine::Server::start()
{
    std::mutex client_mutex;
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    while (true) {
        auto [client_id, action, params] = recv_system.recv_message(server_fd, client_addr, client_addr_len);

        if (action == CONNECTION) {
            std::lock_guard<std::mutex> lock(client_mutex);
            if (current_players < MAX_PLAYERS) {
                client_id = assign_client_id();
                if (client_id > 0) {
                    clients.push_back({client_id, client_addr});
                    current_players++;
                    handle_client_connection(client_id);
                    std::cout << "Client connected with ID: " << static_cast<int>(client_id) << std::endl;
                    send_system.send_message(server_fd, client_addr, client_id, CONNECTION, std::vector<uint16_t>{});
                } else {
                    std::cerr << "Failed to assign client ID." << std::endl;
                }
            } else {
                std::cerr << "Maximum players reached." << std::endl;
            }
        } else {
            handle_action(client_id, action);
        }
    }
}

