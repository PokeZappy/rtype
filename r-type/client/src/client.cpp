/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-cyprien.diederichs
** File description:
** main.cpp
*/

#include "client_config.hpp"

RType::Client::Client() : player_id(0)
{
    if ((client_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    _addr_len = sizeof(_addr);
    memset(&_addr, 0, _addr_len);
    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(PORT);
    _addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    potEngine::engine.registerSystem<potEngine::RenderSystem>();
    potEngine::engine.registerSystem<potEngine::InputSystem>();
    potEngine::engine.registerSystem<potEngine::AnimationSystem>();
    potEngine::engine.registerSystem<potEngine::AudioSystem>();
    potEngine::engine.registerSystem<potEngine::BackgroundSystem>();


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
    auto sendMessageEvent = std::make_shared<potEngine::SendMessageEvent>();
    auto moveClientEvent = std::make_shared<potEngine::MoveClientEvent>();
    auto clientCollisionEvent = std::make_shared<potEngine::ClientCollisionEvent>();
}

void RType::Client::handle_connection()
{
    std::string username;
    std::cout << "Enter your username: ";
    std::cin >> username;

    std::vector<size_t> params_username(username.begin(), username.end());
    send_message(0, potEngine::CONNECTION, params_username, MAX_PLAYERS, client_fd);

    auto [entity_id, event_type, params] = recv_message();
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
        createPlayerEntity(_pos, entity_id);
    }
}

void RType::Client::create_background() {
    auto entity =  potEngine::engine.createEntity();

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile(assetFinder() + "/sprites/space_ background.png"))
        std::cout << assetFinder() << std::endl;
    const std::string &texturePath = assetFinder() + "/sprites/space_ background.png";

    auto positionComponent = std::make_shared<potEngine::PositionComponent>(0, 0);
    auto spriteComponent = std::make_shared<potEngine::SpriteComponent>(texturePath, sf::IntRect(0, 0, 1206, 207), sf::Vector2i(3140, 1080), sf::Vector2i(1206, 207));
    auto static_move_component = std::make_shared<potEngine::staticMoveComponent>(sf::Vector2i(-3000, 0), sf::Vector2i(0, 0));
    potEngine::engine.addComponent(entity, positionComponent);
    potEngine::engine.addComponent(entity, spriteComponent);
    potEngine::engine.addComponent(entity, static_move_component);

    std::cout << "[CLIENT] Background created." << std::endl;
}

void RType::Client::start()
{
    init_subscribe();
    create_background();
    handle_connection();
    setNonBlockingInput();

    std::thread recvThread([this]() {
        while (true) {
            handle_message();
        }
    });

    potEngine::engine.registerSystem<potEngine::ShipAnimationSystem>(player_id);
    potEngine::engine.registerSystem<potEngine::InputToServerSystem>(player_id, client_fd, _addr);
    potEngine::engine.registerSystem<potEngine::ShootEntityClientSystem>(client_fd, _addr);

    std::shared_ptr<potEngine::AEntity> window = potEngine::engine.createWindowEntity();

    potEngine::engine.timer.setTps(60);
    auto startEvent = std::make_shared<potEngine::StartEvent>();
    potEngine::engine.publishEvent(startEvent);
    potEngine::engine.update();
    recvThread.join();
}
