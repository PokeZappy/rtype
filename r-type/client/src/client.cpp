/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** main.cpp
*/

#include "client_config.hpp"

Client::Client() : client_id(0x00)
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

Client::~Client()
{
    close(sockfd);
}

void Client::set_id(uint8_t id)
{
    client_id = id;
}

uint8_t Client::get_id() const
{
    return client_id;
}

void Client::connect_to_server()
{
    potEngine::SendNetworkSystem send_system;
    potEngine::RecvNetworkSystem recv_system;

    send_system.send_message(sockfd, server_addr, 0x00, 0x01);  // Send connection request

    struct sockaddr_in from_addr;
    socklen_t from_addr_len = sizeof(from_addr);

    auto [client_id, action] = recv_system.recv_message(sockfd, from_addr, from_addr_len);
    this->set_id(client_id);

    if (action == 0x01) {
        std::cout << "Connected to server. Client ID: " << static_cast<int>(client_id) << std::endl;
    } else {
        std::cout << "Failed to connect to server.\n";
    }
    send_system.send_message(sockfd, server_addr, this->client_id, 0x02);
}


