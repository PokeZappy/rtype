/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-cyprien.diederichs
** File description:
** main.cpp
*/

#include "client_config.hpp"

RType::Client::Client() : ecs_manager(std::make_shared<potEngine::ECSManager>())
{
    if ((client_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    std::cout << "[CLIENT] Ready to connect to the server...\n";
}


RType::Client::~Client()
{
    close(client_fd);
}

void RType::Client::start()
{
    socklen_t addr_len = sizeof(server_addr);

    std::string username;
    std::cout << "Enter your username: ";
    std::cin >> username;

    std::vector<uint16_t> params_username(username.begin(), username.end());
    auto connectionEventInfo = std::make_shared<potEngine::SendMessageEventInfo>(MAX_PLAYERS, client_fd, server_addr, 0, potEngine::CONNECTION, params_username);
    potEngine::eventBus.publish(connectionEventInfo);

    auto [entity_id, event_type, params] = recv_message(server_addr, addr_len);
    std::cout <<  "EVENTRECV: " << static_cast<int>(event_type) << std::endl;
    if (event_type == potEngine::EventType::CONNECTION) {
        std::cout << "[CLIENT] Connected to the server with ID: " << entity_id << std::endl;
        ecs_manager->createEntity();
    }

    while (true) {
        fd_set read_fds;
        FD_ZERO(&read_fds);
        FD_SET(STDIN_FILENO, &read_fds);

        struct timeval tv;
        tv.tv_sec = 0;
        tv.tv_usec = 500000;

        int activity = select(STDIN_FILENO + 1, &read_fds, nullptr, nullptr, &tv);

        if (activity > 0 && FD_ISSET(STDIN_FILENO, &read_fds)) {
            char input;
            std::cin >> input;

            if (input == 'q') {
                auto disconnectEventInfo = std::make_shared<potEngine::SendMessageEventInfo>(MAX_PLAYERS, client_fd, server_addr, entity_id, potEngine::DISCONNECT, std::vector<uint16_t>{});
                potEngine::eventBus.publish(disconnectEventInfo);
                break;
            }
        }

        auto [entity_id, event_type, params] = recv_message(server_addr, addr_len);
        if (event_type != potEngine::EventType::UNKNOW) {
            std::cout << "[CLIENT] Received event from server: " << event_type << std::endl;
        }
    }

    std::cout << "[CLIENT] Disconnected from server.\n";
}


