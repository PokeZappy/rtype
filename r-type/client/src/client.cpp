/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-cyprien.diederichs
** File description:
** main.cpp
*/

#include "client_config.hpp"

std::string assetFinder();

RType::Client::Client() : player_id(0)
{
    if ((client_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    potEngine::ecsManager.registerSystem<potEngine::RenderSystem>();
    potEngine::ecsManager.registerSystem<potEngine::InputSystem>();
    potEngine::ecsManager.registerSystem<potEngine::AnimationSystem>();
    potEngine::ecsManager.registerSystem<potEngine::AudioSystem>();

    std::cout << "[CLIENT] Ready to connect to the server...\n";
}

RType::Client::~Client()
{
    close(client_fd);
}

void RType::Client::setNonBlockingInput()
{
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
    auto sendMessageToAllExeptEvent = std::make_shared<potEngine::SendMessageToAllExeptEvent>();
    auto sendMessageEvent = std::make_shared<potEngine::SendMessageEvent>();
    auto moveEvent = std::make_shared<potEngine::MoveEvent>();
    auto collisionEvent = std::make_shared<potEngine::CollisionEvent>();
}

void RType::Client::handle_connection()
{
    socklen_t addr_len = sizeof(server_addr);

    std::string username;
    std::cout << "Enter your username: ";
    std::cin >> username;

    std::vector<size_t> params_username(username.begin(), username.end());
    auto connectionEventInfo = std::make_shared<potEngine::SendMessageEventInfo>(MAX_PLAYERS, client_fd, server_addr, 0, potEngine::CONNECTION, params_username);
    potEngine::eventBus.publish(connectionEventInfo);
    potEngine::ecsManager.update(0.0f);
    auto [entity_id, event_type, params] = recv_message(server_addr, addr_len);
    if (event_type == potEngine::EventType::CONNECTION) {
        std::cout << "[CLIENT] Connected to the server with {ID}-[" << static_cast<int>(entity_id) << "]" << std::endl;
        player_id = entity_id;
        std::string player_name = username;
        std::vector<int> position = {0, 0};
        std::vector<size_t> _pos;
        _pos.push_back(potEngine::EntityType::PLAYER);
        _pos.push_back(static_cast<size_t>(player_name.size()));
        for (char c : player_name) {
            _pos.push_back(static_cast<size_t>(c));
        }
        _pos.insert(_pos.end(), position.begin(), position.end());
        potEngine::RecvMessageSystem::createPlayerEntity(_pos, entity_id);
    }
}

void RType::Client::start()
{
    init_subscribe();
    handle_connection();
    setNonBlockingInput();

    socklen_t addr_len = sizeof(server_addr);
    potEngine::ecsManager.registerSystem<potEngine::RecvMessageSystem>(client_fd, server_addr, addr_len, player_id);
    potEngine::ecsManager.registerSystem<potEngine::ShipAnimationSystem>(player_id);
    potEngine::ecsManager.registerSystem<potEngine::InputToServerSystem>(player_id, client_fd, server_addr);
    potEngine::ecsManager.registerSystem<potEngine::ShootEntitySystem>(client_fd, 0.1f);

    std::shared_ptr<potEngine::AEntity> window = potEngine::ecsManager.createWindowEntity();

    auto startEvent = std::make_shared<potEngine::StartEvent>();

    potEngine::eventBus.publish(startEvent);
    potEngine::ecsManager.update(0.016);
}
