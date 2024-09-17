/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-cyprien.diederichs
** File description:
** main.cpp
*/

#include "../../../engine/threading/thread_pool.hpp"
#include "../include/server_config.hpp"
#include "../../../engine/events/event_handler.hpp"

static int error_handling(int ac, char **av)
{
    if (ac != 2) {
        std::cerr << "Usage: ./prog <port>" << std::endl;
        return -84;
    }
    for (int i = 0; av[1][i] != '\0'; i++) {
        if (!std::isdigit(av[1][i])) {
            std::cerr << "Error: Port must be an integer." << std::endl;
            return -84;
        }
    }
    int port = std::atoi(av[1]);
    if (port <= 0 || port > 65535) {
        std::cerr << "Error: Port must be between 1 and 65535." << std::endl;
        return -84;
    }
    return port;
}

static void handle_client(int client_socket)
{
    char buffer[BUFFER_SIZE] = {0};
    std::string welcome_message = "Welcome to the R-TYPE server!\n";
    send(client_socket, welcome_message.c_str(), welcome_message.size(), 0);

    while (true) {
        memset(buffer, 0, BUFFER_SIZE);
        int valread = read(client_socket, buffer, BUFFER_SIZE - 2);
        if (valread <= 0 || buffer[0] == 0x04) {
            std::cout << "Client disconnected (EOF or CTRL+D).\n";
            close(client_socket);
            break;
        }
        buffer[valread - 2] = '\0';
        std::string client_input(buffer);
        std::cout << "Client: {" << client_input << "}\n";
        handle_event(client_input);

        std::string response = "Server received: {" + client_input + "}\n";
        send(client_socket, response.c_str(), response.size(), 0);
    }
}

static void launch_server(int port)
{
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    int opt = 1;

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    } if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    } if (listen(server_fd, MAX_PLAYERS) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    ThreadPool pool(MAX_PLAYERS);
    std::cout << "Server started on port " << port << ". Waiting for clients...\n";
    while (true) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
            perror("accept failed");
            exit(EXIT_FAILURE);
        }
        std::cout << "New client connected.\n";
        pool.enqueue([new_socket] { handle_client(new_socket); });
    }
}

int main(int ac, char **av)
{
    int port = error_handling(ac, av);

    if (port == -84)
        return -84;
    launch_server(port);
    return 0;
}
