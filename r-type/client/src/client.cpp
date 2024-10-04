/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-cyprien.diederichs
** File description:
** main.cpp
*/

#include "client_config.hpp"

RType::Client::Client() : player_id(0), ecs_manager(std::make_shared<potEngine::ECSManager>())
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

void RType::Client::setNonBlockingInput() {
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag &= ~ICANON;
    t.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &t);

    int flags = fcntl(client_fd, F_GETFL, 0);
    fcntl(client_fd, F_SETFL, flags | O_NONBLOCK);
    int flags_ = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags_ | O_NONBLOCK);
}

void RType::Client::init_subscribe()
{
    auto connectionEvent = std::make_shared<potEngine::ConnectionEvent>();
    auto disconnectionEvent = std::make_shared<potEngine::DisconnectionEvent>();
    auto sendMessageToAllEvent = std::make_shared<potEngine::SendMessageToAllEvent>();
    auto sendMessageEvent = std::make_shared<potEngine::SendMessageEvent>();
    auto moveEvent = std::make_shared<potEngine::MoveEvent>();
}

int RType::Client::handle_input()
{
    char input;
    int n = read(STDIN_FILENO, &input, 1);

    if (n > 0) {
        if (input == 'q') {
            auto disconnectEventInfo = std::make_shared<potEngine::SendMessageEventInfo>(MAX_PLAYERS, client_fd, server_addr, player_id, potEngine::DISCONNECT, std::vector<uint16_t>{});
            potEngine::eventBus.publish(disconnectEventInfo);
            std::cout << "[CLIENT] Disconnected from server.\n";
            return 1;
        }
        if (input == 'w') {
            auto moveInfo = std::make_shared<potEngine::SendMessageEventInfo>(MAX_PLAYERS, client_fd, server_addr, player_id, potEngine::MOVE_UP, std::vector<uint16_t>{});
            potEngine::eventBus.publish(moveInfo);
        }
    }
    return 0;
}

void RType::Client::start()
{
    init_subscribe();
    socklen_t addr_len = sizeof(server_addr);

    std::string username;
    std::cout << "Enter your username: ";
    std::cin >> username;

    std::vector<uint16_t> params_username(username.begin(), username.end());
    auto connectionEventInfo = std::make_shared<potEngine::SendMessageEventInfo>(MAX_PLAYERS, client_fd, server_addr, 0, potEngine::CONNECTION, params_username);
    potEngine::eventBus.publish(connectionEventInfo);
    ecs_manager->update(0.0f);
    auto [entity_id, event_type, params] = recv_message(server_addr, addr_len);
    if (event_type == potEngine::EventType::CONNECTION) {
        std::cout << "[CLIENT] Connected to the server with {ID}-[" << static_cast<int>(entity_id) << "]" << std::endl;
        ecs_manager->createEntity(entity_id);
        player_id = entity_id;
    }
    setNonBlockingInput();

    while (true) {
        if (handle_input())
            break;

        auto [entity_id, event_type, params] = recv_message(server_addr, addr_len);
        if (event_type != potEngine::EventType::UNKNOW) {
            std::cout << "[CLIENT] Received event from server: " << static_cast<int>(event_type) << std::endl;
        }
        if (event_type == potEngine::EventType::CONNECTION) {
            std::cout << "[CLIENT] New entity created {ID}-[" << static_cast<int>(entity_id) << "]" << std::endl;
            ecs_manager->createEntity(entity_id);
        }
        if (event_type == potEngine::EventType::MOVE_UP) {
            auto entity = ecs_manager->getEntity(entity_id);
            std::vector<int> convertedParams(params.begin(), params.end());
            entity->getComponent<potEngine::PositionComponent>()->get()->_position = convertedParams;
            std::cout << "[CLIENT] Entity {ID}-[" << std::to_string(static_cast<int>(entity_id))
                << "], {username}-[" << entity->getComponent<potEngine::PlayerComponent>()->get()->username << "], has move to {" << convertedParams[0] << "," << convertedParams[1] << "}" << std::endl;
        }
        ecs_manager->update(0.0f);
    }
}
