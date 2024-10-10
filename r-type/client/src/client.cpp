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
    CLOSESOCKET(client_fd);
}

void RType::Client::setNonBlockingInput() {
    SET_SOCK_NONBLOCKING(client_fd);
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

    sf::Image spriteImage;
    spriteImage.create(100, 100, sf::Color::Blue);

    sf::Texture spriteTexture;
    spriteTexture.loadFromImage(spriteImage);
    sf::Sprite *sprite = new sf::Sprite(spriteTexture);
    sprite->setPosition(100, 100);

    std::shared_ptr<potEngine::RenderComponent> spriteComponent = std::make_shared<potEngine::RenderComponent>(sprite);

    potEngine::ecsManager.addComponent(entity, playerComponent);
    potEngine::ecsManager.addComponent(entity, positionComponent);
    potEngine::ecsManager.addComponent(entity, movementComponent);
    potEngine::ecsManager.addComponent<potEngine::RenderComponent>(entity, spriteComponent);
    std::shared_ptr<potEngine::LifeComponent> lifeComponent = std::make_shared<potEngine::LifeComponent>(3);
    std::shared_ptr<potEngine::CollisionComponent> collisionComponent = std::make_shared<potEngine::CollisionComponent>();
    ecs_manager->addComponent(entity, playerComponent);
    ecs_manager->addComponent(entity, positionComponent);
    ecs_manager->addComponent(entity, movementComponent);
    ecs_manager->addComponent(entity, lifeComponent);
    ecs_manager->addComponent(entity, collisionComponent);
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

void RType::Client::handle_input()
{
    char input;
    int stdfil = STDIN_FILENO;
    int n = read(stdfil, &input, 1);

    if (n > 0) {
        if (input == 'x') {
            auto disconnectEventInfo = std::make_shared<potEngine::SendMessageEventInfo>(MAX_PLAYERS, client_fd, server_addr, player_id, potEngine::DISCONNECT, std::vector<uint16_t>{});
            potEngine::eventBus.publish(disconnectEventInfo);
        }
        if (input == 'z') {
            auto moveInfo = std::make_shared<potEngine::SendMessageEventInfo>(MAX_PLAYERS, client_fd, server_addr, player_id, potEngine::MOVE_UP, std::vector<uint16_t>{});
            potEngine::eventBus.publish(moveInfo);
        }
        if (input == 's') {
            auto moveInfo = std::make_shared<potEngine::SendMessageEventInfo>(MAX_PLAYERS, client_fd, server_addr, player_id, potEngine::MOVE_DOWN, std::vector<uint16_t>{});
            potEngine::eventBus.publish(moveInfo);
        }
        if (input == 'q') {
            auto moveInfo = std::make_shared<potEngine::SendMessageEventInfo>(MAX_PLAYERS, client_fd, server_addr, player_id, potEngine::MOVE_LEFT, std::vector<uint16_t>{});
            potEngine::eventBus.publish(moveInfo);
        }
        if (input == 'd') {
            auto moveInfo = std::make_shared<potEngine::SendMessageEventInfo>(MAX_PLAYERS, client_fd, server_addr, player_id, potEngine::MOVE_RIGHT, std::vector<uint16_t>{});
            potEngine::eventBus.publish(moveInfo);
        }
    }
}

void RType::Client::start() {
    init_subscribe();
    socklen_t addr_len = sizeof(server_addr);
    handle_connection();
    setNonBlockingInput();

    // Initialisation sprites
    // sf::Image spriteImage;
    // spriteImage.create(100, 100, sf::Color::Blue);

    // sf::Texture spriteTexture;
    // spriteTexture.loadFromImage(spriteImage);


    // Initialisation Engine
    // std::shared_ptr<potEngine::AEntity> sprite = ecsManager.createSpriteEntity(spriteTexture);
    std::shared_ptr<potEngine::AEntity> window = potEngine::ecsManager.createWindowEntity();

    std::vector<std::shared_ptr<potEngine::AEntity>> spriteArray;
    // spriteArray.push_back(sprite);
    std::cout << "player id : " << static_cast<int>(player_id) << std::endl;
    spriteArray.push_back(potEngine::ecsManager.getEntity(player_id));

    // Datas needed when triggering events
    auto renderingEventData = std::make_shared<potEngine::EventRender>(window, spriteArray);
    auto inputEventData = std::make_shared<potEngine::ComputeInputEvent>(window);
    auto recvMessageEventData = std::make_shared<potEngine::RecvMessageEventData>(client_fd, server_addr, addr_len, player_id);

    // Instantiating systems needed
    auto renderingSystem = std::make_shared<potEngine::RenderSystem>();
    auto inputSystem = std::make_shared<potEngine::InputSystem>();
    auto recvMessageSystem = std::make_shared<potEngine::RecvMessageSystem>();
    while (ecs_manager->getEntity(player_id)->getComponent<potEngine::LifeComponent>()->get()->life > 0) {
        handle_input();

        // Input to server event
        auto inputServerEvent = std::make_shared<potEngine::InputToServerEvent>(player_id, client_fd, server_addr);


        auto startEvent = std::make_shared<potEngine::StartEvent>();

        startEvent->addEvent(renderingEventData);
        startEvent->addEvent(inputEventData);
        startEvent->addEvent(recvMessageEventData);
        potEngine::eventBus.publish(startEvent);

        potEngine::ecsManager.update(0.016);
    }
}
