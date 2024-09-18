/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-cyprien.diederichs
** File description:
** main.cpp
*/


#include "../include/server_config.hpp"
#include "../../../engine/events/event_handler.hpp"
#include "../../../engine/threading/thread_pool.hpp"
#include "../../../engine/networking/socket.hpp"
#include "serializer/serializer.hpp"

static void handle_event(const std::string& client_input)
{
    if (client_input == "move") {
        std::cout << "Handling move event.\n";
    } else if (client_input == "shoot") {
        std::cout << "Handling shoot event.\n";
    } else {
        std::cout << "Unknown event: " << client_input << "\n";
    }
}

static void handle_client(int client_socket)
{
    char buffer[BUFFER_SIZE] = {0};
    std::string welcome_message = "Welcome to the R-TYPE server!\n";
    send(client_socket, welcome_message.c_str(), welcome_message.size(), 0);

    while (true) {
        memset(buffer, 0, BUFFER_SIZE);
        int valread = read(client_socket, buffer, BUFFER_SIZE);
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

static void launch_server()
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
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    } if (listen(server_fd, MAX_PLAYERS) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    ThreadPool pool(MAX_PLAYERS);
    std::cout << "Server started on port " << PORT << ". Waiting for clients...\n";
    while (true) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
            perror("accept failed");
            exit(EXIT_FAILURE);
        }
        std::cout << "New client connected.\n";
        pool.enqueue([new_socket] { handle_client(new_socket); });
    }
}

int main()
{
    //launch_server();
    Socket serverSocket;
    serverSocket.bindSocket("0.0.0.0", 12345);

    std::string senderIp;
    int senderPort;
    BitSerializer serializer;

    std::cout << "Serveur en attente de messages..." << std::endl;
    while (true) {
        std::string message = serverSocket.receiveFrom(senderIp, senderPort);
        serializer.loadBuffer(std::vector<uint8_t>(message.begin(), message.end()));
        serializer.printBuffer();
        uint16_t messageType = serializer.readBits(8);
        if (messageType == MOVE) {
            std::cout << "Received move event\n";
            serializer.clearBuffer();
            serializer.writeBits(MOVE, 8);
            std::vector<uint8_t> buffer = serializer.getBuffer();
            serializer.printBuffer();
            std::string bufferStr(buffer.begin(), buffer.end());
            serverSocket.sendTo(senderIp, senderPort, bufferStr);
        } else if (messageType == FIRE) {
            std::cout << "Received fire event\n";
            serializer.clearBuffer();
            serializer.writeBits(FIRE, 8);
            std::vector<uint8_t> buffer = serializer.getBuffer();
            serializer.printBuffer();
            std::string bufferStr(buffer.begin(), buffer.end());
            serverSocket.sendTo(senderIp, senderPort, bufferStr);
        } else {
            std::cout << "Received unknown event\n";
            std::cout << "Message reçu de " << senderIp << ":" << senderPort << " -> " << message << std::endl;
            serverSocket.sendTo(senderIp, senderPort, "Message reçu !");
        }
        if (message == "exit") {
            break;
        }
    }
    return 0;
}
