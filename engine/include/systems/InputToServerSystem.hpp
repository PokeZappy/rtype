#pragma once

#include "IEvent.hpp"
#include "EventBus.hpp"
#include "InputInfoEvent.hpp"
#include "SendMessageEvent.hpp"

#include <netinet/in.h>
#include <cmath>
#include <vector>

namespace potEngine {
    class InputToServerSystem : public ASystem {
        public:
            InputToServerSystem(uint8_t playerId, int clientFd, struct sockaddr_in serverAddr) : _playerId(playerId), _clientFd(clientFd), _serverAddr(serverAddr) {
                eventBus.subscribe(this, &InputToServerSystem::handleInputs);
            };
            void handleInputs(std::shared_ptr<BlcEvent> event) {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
                        auto disconnectEventInfo = std::make_shared<potEngine::SendMessageEventInfo>(MAX_PLAYERS, _clientFd, _serverAddr, _playerId, potEngine::DISCONNECT, std::vector<uint16_t>{});
                        potEngine::eventBus.publish(disconnectEventInfo);
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
                        auto moveInfo = std::make_shared<potEngine::SendMessageEventInfo>(MAX_PLAYERS, _clientFd, _serverAddr, _playerId, potEngine::MOVE_UP, std::vector<uint16_t>{});
                        potEngine::eventBus.publish(moveInfo);
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                        auto moveInfo = std::make_shared<potEngine::SendMessageEventInfo>(MAX_PLAYERS, _clientFd, _serverAddr, _playerId, potEngine::MOVE_DOWN, std::vector<uint16_t>{});
                        potEngine::eventBus.publish(moveInfo);
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                        auto moveInfo = std::make_shared<potEngine::SendMessageEventInfo>(MAX_PLAYERS, _clientFd, _serverAddr, _playerId, potEngine::MOVE_LEFT, std::vector<uint16_t>{});
                        potEngine::eventBus.publish(moveInfo);
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                        auto moveInfo = std::make_shared<potEngine::SendMessageEventInfo>(MAX_PLAYERS, _clientFd, _serverAddr, _playerId, potEngine::MOVE_RIGHT, std::vector<uint16_t>{});
                        potEngine::eventBus.publish(moveInfo);
                    }
            }
            void update(float deltaTime) { };
        private:
            uint8_t _playerId;
            int _clientFd;
            struct sockaddr_in _serverAddr;
    };
};