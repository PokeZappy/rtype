#pragma once

#include "IEvent.hpp"
#include "EventBus.hpp"
#include "InputInfoEvent.hpp"
#include "SendMessageEvent.hpp"

#include <netinet/in.h>
#include <cmath>
#include <vector>
#include <chrono>

namespace potEngine {
    class InputToServerSystem : public ASystem {
        public:
            InputToServerSystem(size_t playerId, int clientFd, struct sockaddr_in serverAddr) : _playerId(playerId), _clientFd(clientFd), _serverAddr(serverAddr) {
                lastUpdateTime = std::chrono::steady_clock::now();
                eventBus.subscribe(this, &InputToServerSystem::handleInputs);
            };
            std::chrono::time_point<std::chrono::steady_clock> lastUpdateTime;
            float updateInterval = 0.016f;

            static sf::IntRect changeShootAnimationFrame(int frame) {
                return sf::IntRect(sf::Vector2i(2 + 33 * (frame - 1) + std::abs((frame - 1) / 3), 51), sf::Vector2i(32, 30));
            }
            int createShootAnimation(std::shared_ptr<AEntity> playerEntity) {
                auto shootAnimationEntity = ecsManager.createEntity();
                auto playerPositionComponent = playerEntity->getComponent<PositionComponent>();
                auto playerSpriteComponent = playerEntity->getComponent<SpriteComponent>();
                if (!playerPositionComponent || !playerSpriteComponent)
                    return (-1);
                auto playerPosition = playerPositionComponent->get()->_position;
                auto playerIntRect = playerSpriteComponent->get()->getSprite().getTextureRect();
                auto positionComponent = std::make_shared<PositionComponent>(playerPosition[0] + playerIntRect.width * (playerSpriteComponent->get()->getSprite().getScale().x), playerPosition[1] - 14);
                auto animationComponent = std::make_shared<AnimationComponent>(7, 0.15, true, changeShootAnimationFrame);

                const std::string texturePath = "/home/Tom/Bureau/Projet/EPITECH/B-CPP-500-LYN-5-1-rtype-cyprien.diederichs/r-type/assets/sprites/r-typesheet1.gif";
                auto spriteComponent = std::make_shared<SpriteComponent>(texturePath, sf::IntRect(sf::Vector2i(2, 51), sf::Vector2i(32, 30)));

                ecsManager.addComponent(shootAnimationEntity, positionComponent);
                ecsManager.addComponent(shootAnimationEntity, animationComponent);
                ecsManager.addComponent(shootAnimationEntity, spriteComponent);
                return (shootAnimationEntity->getID());
            }

            void updateShootAnimationPosition(std::shared_ptr<AEntity> playerEntity) {
                auto shootAnimationEntity = ecsManager.getEntity(playerEntity->getComponent<PlayerComponent>()->get()->getShootAnimationEntityId().value());
                auto playerPositionComponent = playerEntity->getComponent<PositionComponent>();
                auto playerSpriteComponent = playerEntity->getComponent<SpriteComponent>();
                if (!playerPositionComponent || !playerSpriteComponent)
                    return;
                auto playerPosition = playerPositionComponent->get()->_position;
                auto playerIntRect = playerSpriteComponent->get()->getSprite().getTextureRect();
                auto positionComponent = shootAnimationEntity->getComponent<PositionComponent>();
                positionComponent->get()->_position[0] = playerPosition[0] + playerIntRect.width * (playerSpriteComponent->get()->getSprite().getScale().x);
                positionComponent->get()->_position[1] = playerPosition[1] - 14;
            }

            void handleInputs(std::shared_ptr<BlcEvent> event) {

                auto currentTime = std::chrono::steady_clock::now();
                std::chrono::duration<float> elapsedTime = currentTime - lastUpdateTime;
                if (elapsedTime.count() >= updateInterval) {
                    lastUpdateTime = currentTime;
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
                        auto disconnectEventInfo = std::make_shared<potEngine::SendMessageEventInfo>(MAX_PLAYERS, _clientFd, _serverAddr, _playerId, potEngine::DISCONNECT, std::vector<size_t>{});
                        potEngine::eventBus.publish(disconnectEventInfo);
                        eventBus.publish(std::make_shared<StopMainLoopEvent>());
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
                        auto moveInfo = std::make_shared<potEngine::SendMessageEventInfo>(MAX_PLAYERS, _clientFd, _serverAddr, _playerId, potEngine::MOVE_UP, std::vector<size_t>{});
                        potEngine::eventBus.publish(moveInfo);
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                        auto moveInfo = std::make_shared<potEngine::SendMessageEventInfo>(MAX_PLAYERS, _clientFd, _serverAddr, _playerId, potEngine::MOVE_DOWN, std::vector<size_t>{});
                        potEngine::eventBus.publish(moveInfo);
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                        auto moveInfo = std::make_shared<potEngine::SendMessageEventInfo>(MAX_PLAYERS, _clientFd, _serverAddr, _playerId, potEngine::MOVE_LEFT, std::vector<size_t>{});
                        potEngine::eventBus.publish(moveInfo);
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                        auto moveInfo = std::make_shared<potEngine::SendMessageEventInfo>(MAX_PLAYERS, _clientFd, _serverAddr, _playerId, potEngine::MOVE_RIGHT, std::vector<size_t>{});
                        potEngine::eventBus.publish(moveInfo);
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
                        auto startStage = std::make_shared<potEngine::SendMessageEventInfo>(MAX_PLAYERS, _clientFd, _serverAddr, _playerId, potEngine::START_STAGE, std::vector<uint16_t>{});
                        potEngine::eventBus.publish(startStage);
                    }
                    // if (event->type == sf::Event::KeyReleased) {
                    //     if (event->key == sf::Keyboard::L) {
                    //         auto startStage = std::make_shared<potEngine::SendMessageEventInfo>(MAX_PLAYERS, _clientFd, _serverAddr, _playerId, potEngine::START_STAGE, std::vector<uint16_t>{});
                    //         potEngine::eventBus.publish(startStage);
                    //     }
                    // }
                    auto playerEntity = ecsManager.getEntity(_playerId);
                    auto playerComponent = playerEntity->getComponent<PlayerComponent>();
                    if (!playerComponent)
                        return;
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                        if (!playerComponent->get()->getShootAnimationEntityId().has_value()) {
                            int shootAnimationEntityId = createShootAnimation(playerEntity);
                            if (shootAnimationEntityId != -1)
                                playerComponent->get()->setShootAnimationEntityId(shootAnimationEntityId);
                            // TODO : informer le serveur que le shoot est en cours
                        } else {
                            updateShootAnimationPosition(playerEntity);
                        }
                    } else {
                        if (playerComponent->get()->getShootAnimationEntityId().has_value()) {
                            ecsManager.removeEntity(playerComponent->get()->getShootAnimationEntityId().value());
                            playerComponent->get()->getShootAnimationEntityId().reset();
                            auto moveInfo = std::make_shared<potEngine::SendMessageEventInfo>(MAX_PLAYERS, _clientFd, _serverAddr, _playerId, potEngine::SHOOT, std::vector<size_t>{});
                            potEngine::eventBus.publish(moveInfo);
                        }
                    }
                }
            }
            void update(float deltaTime) { };
        private:
            size_t _playerId;
            int _clientFd;
            struct sockaddr_in _serverAddr;
    };
};