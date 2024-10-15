/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-cyprien.diederichs
** File description:
** main.cpp
*/

#include "client_config.hpp"
#include "Config.hpp"

std::string assetFinder();

RType::Client::Client(const std::string &ip, int port) : player_id(0)
{
    INIT_WINSOCK();
    if ((client_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    _addr_len = sizeof(_addr);
    memset(&_addr, 0, _addr_len);
    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(port);
    _addr.sin_addr.s_addr = inet_addr(ip.c_str());

    potEngine::engine.registerSystem<potEngine::RenderSystem>();
    potEngine::engine.registerSystem<potEngine::InputSystem>();
    potEngine::engine.registerSystem<potEngine::AnimationSystem>();
    potEngine::engine.registerSystem<potEngine::AudioSystem>();
    potEngine::engine.registerSystem<potEngine::BackgroundSystem>();




    // std::cout << "[CLIENT] Ready to connect to the server...\n";
}

void RType::Client::parseEnemies()
{
    try {
        libconfig::Config cfg;
        cfg.readFile((assetFinder() + "/../shared/config/enemies.cfg").c_str());
        libconfig::Setting &root = cfg.getRoot();

        for (int i = 0; i < root["enemies"].getLength(); i++) {
            libconfig::Setting &enemy = root["enemies"][i];
            struct potEngine::EnemyInfo enemyInfo;
            enemyInfo.id = enemy["id"];
            enemyInfo.hp = enemy["hp"];
            enemyInfo.speed = enemy["speed"];
            enemyInfo.movePattern = enemy["move_pattern"].c_str();
            enemyInfo.attackPattern = enemy["attack_pattern"].c_str();
            enemyInfo.texturePath = enemy["texturePath"].c_str();
            enemyInfo.textureRect.push_back(enemy["textureRect"]["x"]);
            enemyInfo.textureRect.push_back(enemy["textureRect"]["y"]);
            enemyInfo.textureRect.push_back(enemy["textureRect"]["w"]);
            enemyInfo.textureRect.push_back(enemy["textureRect"]["h"]);
            // enemyInfo.name = monsterName;
            _parsedEnemies.push_back(std::make_shared<struct potEngine::EnemyInfo>(enemyInfo));
        }
    } catch (const libconfig::FileIOException &fioex) {
        std::cerr << "I/O error while reading file." << std::endl;
        return;
    } catch (const libconfig::ParseException &pex) {
        std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine() << " - " << pex.getError() << std::endl;
        return;
    } catch (const libconfig::SettingNotFoundException &nfex) {
        std::cerr << "Setting not found in configuration file." << nfex.getPath() << std::endl;
        return;
    } catch (const libconfig::SettingTypeException &stex) {
        std::cerr << "Setting type error in configuration file." << stex.getPath() << std::endl;
        return;
    }
}

RType::Client::~Client()
{
    CLOSESOCKET(client_fd)
}

void RType::Client::setNonBlockingInput() {
    SET_SOCK_NONBLOCKING(client_fd)
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
        // std::cout << "[CLIENT] Connected to the server with {ID}-[" << static_cast<int>(entity_id) << "]" << std::endl;
        player_id = entity_id;
        std::string player_name = username;
        std::vector<float> position = {0, 0};
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

    potEngine::engine.registerSystem<potEngine::MoveClientEntitySystem>(client_fd, _addr);
    potEngine::engine.registerSystem<potEngine::ShipAnimationSystem>(player_id);

    auto inputEvent = std::make_shared<potEngine::InputToServerEvent>(player_id, client_fd, _addr);
    std::shared_ptr<potEngine::AEntity> window = potEngine::engine.createWindowEntity();

    potEngine::engine.timer.setTps(60);
    auto startEvent = std::make_shared<potEngine::StartEvent>();
    potEngine::engine.publishEvent(startEvent);
    potEngine::engine.update();
    recvThread.join();
}
