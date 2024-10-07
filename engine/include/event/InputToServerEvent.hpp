#pragma once

#include "IEvent.hpp"
#include "EventBus.hpp"
#include "InputInfoEvent.hpp"
#include "SendMessageEvent.hpp"

#include <netinet/in.h>
#include <cmath>
#include <vector>

namespace potEngine {
    class InputToServerEvent : public IEvent {
        public:
            InputToServerEvent(uint8_t playerId, int clientFd, struct sockaddr_in serverAddr) : _playerId(playerId), _clientFd(clientFd), _serverAddr(serverAddr) {
                eventBus.subscribe(this, &InputToServerEvent::handleInputs);
            };

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
                // Création texture et sprite
                sf::Texture texture;
                texture.loadFromFile("/home/samuel/tek3/rtpe/r-type/assets/sprites/r-typesheet1.gif");
                auto spriteComponent = std::make_shared<SpriteComponent>(texture, sf::IntRect(sf::Vector2i(2, 51), sf::Vector2i(32, 30)));
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


            void handleInputs(std::shared_ptr<InputInfoEvent> event) {
                if (event->type == sf::Event::KeyPressed) {
                    if (event->key == sf::Keyboard::X) {
                        auto disconnectEventInfo = std::make_shared<potEngine::SendMessageEventInfo>(MAX_PLAYERS, _clientFd, _serverAddr, _playerId, potEngine::DISCONNECT, std::vector<uint16_t>{});
                        potEngine::eventBus.publish(disconnectEventInfo);
                    }
                    if (event->key == sf::Keyboard::Z) {
                        auto moveInfo = std::make_shared<potEngine::SendMessageEventInfo>(MAX_PLAYERS, _clientFd, _serverAddr, _playerId, potEngine::MOVE_UP, std::vector<uint16_t>{});
                        potEngine::eventBus.publish(moveInfo);
                    }
                    if (event->key == sf::Keyboard::S) {
                        auto moveInfo = std::make_shared<potEngine::SendMessageEventInfo>(MAX_PLAYERS, _clientFd, _serverAddr, _playerId, potEngine::MOVE_DOWN, std::vector<uint16_t>{});
                        potEngine::eventBus.publish(moveInfo);
                    }
                    if (event->key == sf::Keyboard::Q) {
                        auto moveInfo = std::make_shared<potEngine::SendMessageEventInfo>(MAX_PLAYERS, _clientFd, _serverAddr, _playerId, potEngine::MOVE_LEFT, std::vector<uint16_t>{});
                        potEngine::eventBus.publish(moveInfo);
                    }
                    if (event->key == sf::Keyboard::D) {
                        auto moveInfo = std::make_shared<potEngine::SendMessageEventInfo>(MAX_PLAYERS, _clientFd, _serverAddr, _playerId, potEngine::MOVE_RIGHT, std::vector<uint16_t>{});
                        potEngine::eventBus.publish(moveInfo);
                    }

                    if (event->key == sf::Keyboard::Space) {
                        auto playerEntity = ecsManager.getEntity(_playerId);
                        auto playerComponent = playerEntity->getComponent<PlayerComponent>();
                        if (playerComponent) {
                            if (!playerComponent->get()->getShootAnimationEntityId().has_value()) {
                                std::cout << "je crée l'animation de shoot" << std::endl;
                                // on crée l'animation de shoot 
                                int shootAnimationEntityId = createShootAnimation(playerEntity);
                                if (shootAnimationEntityId != -1)
                                    playerComponent->get()->setShootAnimationEntityId(shootAnimationEntityId);
                                // TODO : informer le serveur que le shoot est en cours
                            } else {
                                // animation de tir existe déjà, on update la position de l'animation pour concorder avec le joueur
                                updateShootAnimationPosition(playerEntity);
                            }
                        }
                    }
                }
                if (event->type == sf::Event::KeyReleased) {
                    if (event->key == sf::Keyboard::Space) {

                    }
                }
            }
        private:
            uint8_t _playerId;
            int _clientFd;
            struct sockaddr_in _serverAddr;
    };
};