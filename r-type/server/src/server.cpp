/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-cyprien.diederichs
** File description:
** server.cpp
*/

#include "server_config.hpp"

/*!
* @brief Initialize the server with the specified port.
*
* This function creates a socket, binds it to the specified port, and prepares the server to accept clients.
*
* @param port The port number to bind the server to.
*/
void RType::Server::init(int port) {
    if ((server_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    _addr_len = sizeof(_addr);
    memset(&_addr, 0, _addr_len);
    _addr.sin_family = AF_INET;
    _addr.sin_addr.s_addr = INADDR_ANY;
    _addr.sin_port = htons(port);
    if (bind(server_fd, (const struct sockaddr*)&_addr, _addr_len) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    std::cout << "[SERVER] started on port " << port << ". Waiting for clients...\n";
}

/*!
* @brief Default constructor for the Server class.
*
* Initializes the server with the default port.
*/
RType::Server::Server() : current_players(0)
{
    init(PORT);
}

/*!
* @brief Parameterized constructor for the Server class.
*
* Initializes the server with the specified port.
*
* @param port The port number to bind the server to.
*/
RType::Server::Server(int port) : current_players(0)
{
    init(port);
}

/*!
* @brief Destructor for the Server class.
*
* Closes the server socket.
*/
RType::Server::~Server()
{
    close(server_fd);
}

/*!
* @brief Initialize event subscriptions for the server.
*
* This function sets up the server to listen for various events.
*/
void RType::Server::init_subscribe()
{
    auto connectionEvent = std::make_shared<potEngine::ConnectionEvent>();
    auto disconnectionEvent = std::make_shared<potEngine::DisconnectionEvent>();
    auto sendMessageToAllEvent = std::make_shared<potEngine::SendMessageToAllEvent>();
    auto sendAllDataEvent = std::make_shared<potEngine::SendAllDataEvent>();
    auto sendMessageToAllExeptEvent = std::make_shared<potEngine::SendMessageToAllExeptEvent>();
    auto sendMessageEvent = std::make_shared<potEngine::SendMessageEvent>();
    auto MoveServerEvent = std::make_shared<potEngine::MoveServerEvent>();
    auto collisionEvent = std::make_shared<potEngine::CollisionEvent>();
    auto entityCreateEvent = std::make_shared<potEngine::EntityCreateEvent>();
}

/*!
* @brief Set the server socket to non-blocking mode.
*
* This function modifies the server socket to not block input.
*/
void RType::Server::setNonBlockingInput()
{
    int flags = fcntl(server_fd, F_GETFL, 0);
    fcntl(server_fd, F_SETFL, flags | O_NONBLOCK);
}

/*!
* @brief Start the server.
*
* This function starts the main server loop and the reception of messages in a separate thread.
*/
void RType::Server::start()
{
    init_subscribe();
    setNonBlockingInput();

    std::thread recvThread([this]() {
        while (true) {
            handle_message();
        }
    });

    potEngine::engine.registerSystem<potEngine::MoveServerEntitySystem>();

    potEngine::engine.timer.setTps(20);
    auto startEvent = std::make_shared<potEngine::StartEvent>();
    potEngine::engine.publishEvent(startEvent);
    potEngine::engine.update();
    recvThread.join();
}
