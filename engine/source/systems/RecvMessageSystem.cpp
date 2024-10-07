#include "RecvMessageSystem.hpp"
#include <iostream>
#include <cmath>
#include "PositionComponent.hpp"
#include "PlayerComponent.hpp"
#include "MovementComponent.hpp"
#include "LifeComponent.hpp"
#include "CollisionComponent.hpp"
#include "SpriteComponent.hpp"

namespace potEngine
{
    RecvMessageSystem::RecvMessageSystem(int cliFd, struct sockaddr_in servAddr, socklen_t adLen, uint8_t id) : _clientFd(cliFd), _addrLen(adLen), _playerId(id)
    {
        // _signature.set(AComponent::getID<RenderComponent>(), true);
        eventBus.subscribe(this, &RecvMessageSystem::updateSystem);
    }

    RecvMessageSystem::~RecvMessageSystem() {

    }

    std::tuple<uint8_t, potEngine::EventType, std::vector<uint16_t>> RecvMessageSystem::recv_message()
    {
        uint8_t buffer[1024]; // TODO mettre BUFFER_SIZE macro
        ssize_t recv_len = recvfrom(_clientFd, buffer, sizeof(buffer), 0, (struct sockaddr*)&_addr, &_addrLen);

        if (recv_len < 0) {
            return std::make_tuple(0, potEngine::EventType::UNKNOW, std::vector<uint16_t>{});
        }

        int entity_id_bits = std::ceil(std::log2(4 + 1)); // TODO mettre macro MAX_PLAYERS
        int action_bits = 8 - entity_id_bits;

        uint8_t entity_id = (buffer[0] >> action_bits) & ((1 << entity_id_bits) - 1);
        uint8_t action = buffer[0] & ((1 << action_bits) - 1);

        potEngine::EventType event_type = static_cast<potEngine::EventType>(action);

        std::vector<uint16_t> params;
        for (ssize_t i = 1; i + 1 < recv_len; i += 2) {
            uint16_t param = (buffer[i] << 8) | buffer[i + 1];
            params.push_back(param);
        }

        return std::make_tuple(entity_id, event_type, params);
    }

    std::string assetFinder();

    void RecvMessageSystem::createPlayerEntity(std::vector<uint16_t> params, uint8_t entity_id)
    {
        uint16_t username_length = params[1];
        std::string username;
        for (size_t i = 0; i < username_length; ++i) {
            username += static_cast<char>(params[2 + i]);
        }
        std::vector<uint16_t> position(params.begin() + 2 + username_length, params.end());

        auto entity = ecsManager.createEntity(entity_id);

        sf::Texture playerTexture;
        libconfig::Config sconfig;
        try {

            sconfig.readFile("/home/fifster/tek3/r-type/rtype/r-type/config/config.cfg");
            } catch (const libconfig::FileIOException &fioex) {
        std::cerr << "File I/O error: Unable to read configuration file." << std::endl;
    } catch (const libconfig::ParseException &pex) {
        // This provides more specific details about where the parse error occurred
        std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine() 
                  << " - " << pex.getError() << std::endl;
    } catch (const libconfig::SettingNotFoundException &nfex) {
        // This gives the exact setting that was not found
        std::cerr << "Missing setting in configuration file: " << nfex.getPath() << std::endl;

    } catch (const std::exception &e) {
        // Catch other general exceptions
        std::cerr << "Error config: " << e.what() << std::endl;
    }
        if (!playerTexture.loadFromFile(assetFinder() + sconfig.lookup("graphics").lookup("sprites").lookup("player").c_str()))
            std::cout << assetFinder() << std::endl;
        else
            std::cout << "Texture loaded" << std::endl;

        std::shared_ptr<PlayerComponent> playerComponent = std::make_shared<PlayerComponent>(username);
        std::shared_ptr<PositionComponent> positionComponent = std::make_shared<PositionComponent>(position[0], position[1]);
        try {
            std::shared_ptr<MovementComponent> movementComponent = std::make_shared<MovementComponent>(sconfig.lookup("graphics").lookup("move_on_screen"));
            ecsManager.addComponent(entity, movementComponent);
        } catch (const std::exception& e) {
            std::cerr << "Error mvt : " << e.what() << std::endl;
        }
        std::shared_ptr<LifeComponent> lifeComponent = std::make_shared<LifeComponent>(3);
        std::shared_ptr<CollisionComponent> collisionComponent = std::make_shared<CollisionComponent>();
        try {
            std::shared_ptr<SpriteComponent> spriteComponent = std::make_shared<SpriteComponent>(playerTexture, sf::IntRect(sf::Vector2i(66, 1), sf::Vector2i(33, 17)));
            ecsManager.addComponent(entity, spriteComponent);
        } catch (const std::exception& e) {
            std::cerr << "Error sprites: " << e.what() << std::endl;
        }
        ecsManager.addComponent(entity, playerComponent);
        ecsManager.addComponent(entity, positionComponent);
        ecsManager.addComponent(entity, lifeComponent);
        ecsManager.addComponent(entity, collisionComponent);

        std::cout << "[CLIENT] New entity created {ID}-[" << static_cast<int>(entity_id)
            << "] {username}-[" << username <<  "] {POS}-[" << position[0] << "," << position[1] << "]." << std::endl;
    }

    void handleCreateEntity(std::vector<uint16_t> params, uint8_t entity_id)
    {
        uint16_t type = params[0];

        if (type == EntityType::PLAYER)
            return RecvMessageSystem::createPlayerEntity(params, entity_id);
    }

    void RecvMessageSystem::updateSystem(std::shared_ptr<BlcEvent> event) {
        // std::cout << "RECEIVE" << std::endl;
        auto [entity_id, event_type, params] = recv_message();
        if (event_type != EventType::UNKNOW) {
            std::cout << "[CLIENT] Received event from server: " << static_cast<int>(event_type) << std::endl;
        }
        if (event_type == EventType::CONNECTION) {
            createPlayerEntity(params, entity_id);
        }
        if (event_type == EventType::DISCONNECT) {
            if (entity_id == _playerId) {
                std::cout << "[CLIENT] Disconnected from server." << std::endl;
                // TODO fermer le client ici.
                return;
            }
            std::cout << "[CLIENT] Client with {ID}-[" << static_cast<int>(entity_id) << "] disconnected from server." << std::endl;
        }
        if (event_type == EventType::MOVE_UP || event_type == EventType::MOVE_DOWN || event_type == EventType::MOVE_LEFT || event_type == EventType::MOVE_RIGHT) {
            auto entity = ecsManager.getEntity(entity_id);
            if (!entity) {
                std::cout << "[CLIENT] {ID}-[" << static_cast<int>(entity_id) << "] not found." << std::endl;
                return;
            }
            std::vector<int> convertedParams(params.begin(), params.end());
            entity->getComponent<potEngine::PositionComponent>()->get()->_position = convertedParams;
            std::cout << "[CLIENT] Entity {ID}-[" << std::to_string(static_cast<int>(entity_id))
                << "], {username}-[" << entity->getComponent<potEngine::PlayerComponent>()->get()->username << "], has move to {" << convertedParams[0] << "," << convertedParams[1] << "}" << std::endl;
        }
        if (event_type == EventType::INFORMATION) {
            // ici le joueur recoit les informations de toutes les entities déja présente
            handleCreateEntity(params, entity_id);
        }
    }
}