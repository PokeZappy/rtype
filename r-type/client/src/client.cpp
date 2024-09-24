/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** main.cpp
*/

#include "client_config.hpp"

potEngine::Client::Client() : client_id(0x00)
{
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {
        std::cerr << "Invalid server IP address" << std::endl;
        exit(EXIT_FAILURE);
    }
}

potEngine::Client::~Client()
{
    close(sockfd);
}

void potEngine::Client::set_id(uint8_t id)
{
    client_id = id;
}

uint8_t potEngine::Client::get_id() const
{
    return client_id;
}

int potEngine::Client::handle_input()
{
    potEngine::SendNetworkSystem send_system;

    char input;
    std::cout << "Enter: ";
    std::cin >> input;

    uint8_t action = 0;
    switch (input) {
        case 'w': action = MOVE_UP; break;
        case 's': action = MOVE_DOWN; break;
        case 'a': action = MOVE_LEFT; break;
        case 'd': action = MOVE_RIGHT; break;
        case 'q': action = DISCONNECT; return 1;
        default: std::cout << "Invalid input\n"; return 0;
    }
    send_system.send_message(sockfd, server_addr, this->client_id, action, std::vector<uint16_t>{});
    return 0;
}

void potEngine::Client::connect_to_server()
{
    potEngine::SendNetworkSystem send_system;
    potEngine::RecvNetworkSystem recv_system;

    send_system.send_message(sockfd, server_addr, 0x00, CONNECTION, std::vector<uint16_t>{});

    struct sockaddr_in from_addr;
    socklen_t from_addr_len = sizeof(from_addr);

    auto [client_id, action, params] = recv_system.recv_message(sockfd, from_addr, from_addr_len);
    this->set_id(client_id);

    if (action == CONNECTION) {
        std::cout << "Connected to server. Client ID: " << static_cast<int>(client_id) << std::endl;

        std::thread receive_thread([this, &recv_system]() {
            struct sockaddr_in from_addr;
            socklen_t from_addr_len = sizeof(from_addr);
            while (true) {
                auto [sender_id, action, params] = recv_system.recv_message(sockfd, from_addr, from_addr_len);
                if (action == MOVE_UP || action == MOVE_DOWN || action == MOVE_LEFT || action == MOVE_RIGHT) {
                    int x = params[0];
                    int y = params[1];
                    std::cout << "Position updated to (" << x << ", " << y << ") for client " << static_cast<int>(sender_id) << ".\n";
                } else if (action == DISCONNECT) {
                    std::cout << "Server has disconnected the client." << std::endl;
                    break;
                }
            }
        });
        while (handle_input() == 0);
        send_system.send_message(sockfd, server_addr, this->client_id, DISCONNECT, std::vector<uint16_t>{});
        if (receive_thread.joinable()) {
            receive_thread.join();
        }
    } else {
        std::cout << "Failed to connect to server.\n";
    }
}
