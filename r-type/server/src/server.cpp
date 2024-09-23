/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-cyprien.diederichs
** File description:
** main.cpp
*/

#include "server_config.hpp"

Server::Server() : current_players(0)
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
Server::~Server()
{
    close(server_fd);
}

uint8_t Server::assign_client_id()
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

void Server::remove_client(uint8_t client_id)
{
    clients.erase(std::remove_if(clients.begin(), clients.end(), [client_id](const ClientInfo& client) {
        return client.client_id == client_id;
    }), clients.end());
}

void Server::start()
{
    potEngine::RecvNetworkSystem recv_system;
    potEngine::SendNetworkSystem send_system;

    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    while (true) {
        auto [client_id, action] = recv_system.recv_message(server_fd, client_addr, client_addr_len);

        if (action == CONNECTION) {
            if (current_players < MAX_PLAYERS) {
                client_id = assign_client_id();
                if (client_id > 0) {
                    clients.push_back({client_id, client_addr});
                    current_players++;
                    std::cout << "Client connected with ID: " << static_cast<int>(client_id) << std::endl;
                    send_system.send_message(server_fd, client_addr, client_id, CONNECTION);
                }
            }
        } else {
            handle_action(client_id, action);
        }
    }
}

void Server::handle_action(uint8_t client_id, uint8_t action)
{
    auto it = std::find_if(clients.begin(), clients.end(), [client_id](const ClientInfo& client) {
        return client.client_id == client_id;
    });

    if (it != clients.end()) {
        switch (action) {
            case MOVE_UP:
                std::cout << "Client " << static_cast<int>(client_id) << " moves up.\n";
                break;
            case MOVE_DOWN:
                std::cout << "Client " << static_cast<int>(client_id) << " moves down.\n";
                break;
            case MOVE_LEFT:
                std::cout << "Client " << static_cast<int>(client_id) << " moves left.\n";
                break;
            case MOVE_RIGHT:
                std::cout << "Client " << static_cast<int>(client_id) << " moves right.\n";
                break;
            case DISCONNECT :
                std::cout << "Client " << static_cast<int>(client_id) << " is disconnecting.\n";
                remove_client(client_id);
                current_players--;
                break;
            default:
                std::cout << "Unknown action.\n";
        }
    }
}

