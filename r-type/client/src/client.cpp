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
    auto sendMessageToAllExeptEvent = std::make_shared<potEngine::SendMessageToAllExeptEvent>();
    auto sendMessageEvent = std::make_shared<potEngine::SendMessageEvent>();
    auto moveEvent = std::make_shared<potEngine::MoveEvent>();
}

void RType::Client::handle_create_entity_player(uint8_t entity_id, std::string username)
{
    player_id = entity_id;
    auto entity = potEngine::ecsManager.createEntity(entity_id);

    std::shared_ptr<potEngine::PlayerComponent> playerComponent = std::make_shared<potEngine::PlayerComponent>(username);
    std::shared_ptr<potEngine::PositionComponent> positionComponent = std::make_shared<potEngine::PositionComponent>(0.0f, 0.0f);
    std::shared_ptr<potEngine::MovementComponent> movementComponent = std::make_shared<potEngine::MovementComponent>(1.0f);

    potEngine::ecsManager.addComponent(entity, playerComponent);
    potEngine::ecsManager.addComponent(entity, positionComponent);
    potEngine::ecsManager.addComponent(entity, movementComponent);
}

void RType::Client::handle_connection()
{
    socklen_t addr_len = sizeof(server_addr);

    std::string username;
    std::cout << "Enter your username: ";
    std::cin >> username;

    std::vector<uint16_t> params_username(username.begin(), username.end());
    auto connectionEventInfo = std::make_shared<potEngine::SendMessageEventInfo>(MAX_PLAYERS, client_fd, server_addr, 0, potEngine::CONNECTION, params_username);
    potEngine::eventBus.publish(connectionEventInfo);
    potEngine::ecsManager.update(0.0f);
    auto [entity_id, event_type, params] = recv_message(server_addr, addr_len);
    if (event_type == potEngine::EventType::CONNECTION) {
        std::cout << "[CLIENT] Connected to the server with {ID}-[" << static_cast<int>(entity_id) << "]" << std::endl;
        handle_create_entity_player(entity_id, username);
    }
}

void RType::Client::start()
{
    init_subscribe();
    socklen_t addr_len = sizeof(server_addr);
    handle_connection();
    setNonBlockingInput();

    // Initialisation sprites
    sf::Image spriteImage;
    spriteImage.create(100, 100, sf::Color::Blue);

    sf::Texture spriteTexture;
    spriteTexture.loadFromImage(spriteImage);


    // Initialisation Engine
    potEngine::ECSManager ecsManager;

    std::shared_ptr<potEngine::AEntity> sprite = ecsManager.createSpriteEntity(spriteTexture);
    std::shared_ptr<potEngine::AEntity> window = ecsManager.createWindowEntity();

    std::vector<std::shared_ptr<potEngine::AEntity>> spriteArray;
    spriteArray.push_back(sprite);

    // Datas needed when triggering events
    auto renderingEventData = std::make_shared<potEngine::EventRender>(window, spriteArray);
    auto inputEventData = std::make_shared<potEngine::ComputeInputEvent>(window);
    auto recvMessageEventData = std::make_shared<potEngine::RecvMessageEventData>(client_fd, server_addr, addr_len, player_id);

    // Instantiating systems needed
    auto renderingSystem = std::make_shared<potEngine::RenderSystem>();
    auto inputSystem = std::make_shared<potEngine::InputSystem>();
    auto recvMessageSystem = std::make_shared<potEngine::RecvMessageSystem>();

    // Input to server event
    auto inputServerEvent = std::make_shared<potEngine::InputToServerEvent>(player_id, client_fd, server_addr);


    auto startEvent = std::make_shared<potEngine::StartEvent>();

    startEvent->addEvent(renderingEventData);
    startEvent->addEvent(inputEventData);
    startEvent->addEvent(recvMessageEventData);
    potEngine::eventBus.publish(startEvent);

    ecsManager.update(0.016);
}
