#pragma once

#include "IEvent.hpp"
#include "EventBus.hpp"
#include "InputInfoEvent.hpp"
#include "SendMessageEvent.hpp"

#include "cross_config.hpp"
#include <cmath>
#include <vector>

namespace potEngine {
    class InputToServerEvent : public IEvent {
        public:
            InputToServerEvent(uint8_t playerId, int clientFd, struct sockaddr_in serverAddr) : _playerId(playerId), _clientFd(clientFd), _serverAddr(serverAddr) {
                eventBus.subscribe(this, &InputToServerEvent::handleInputs);
            };
            void handleInputs(std::shared_ptr<InputInfoEvent> event) {
                if (event->type == sf::Event::KeyPressed) {
                    if (event->key == sf::Keyboard::X) {
                        auto disconnectEventInfo = std::make_shared<potEngine::SendMessageEventInfo>(4, _clientFd, _serverAddr, _playerId, potEngine::DISCONNECT, std::vector<uint16_t>{});
                        potEngine::eventBus.publish(disconnectEventInfo);
                    }
                    if (event->key == sf::Keyboard::Z) {
                        auto moveInfo = std::make_shared<potEngine::SendMessageEventInfo>(4, _clientFd, _serverAddr, _playerId, potEngine::MOVE_UP, std::vector<uint16_t>{});
                        potEngine::eventBus.publish(moveInfo);
                    }
                    if (event->key == sf::Keyboard::S) {
                        auto moveInfo = std::make_shared<potEngine::SendMessageEventInfo>(4, _clientFd, _serverAddr, _playerId, potEngine::MOVE_DOWN, std::vector<uint16_t>{});
                        potEngine::eventBus.publish(moveInfo);
                    }
                    if (event->key == sf::Keyboard::Q) {
                        auto moveInfo = std::make_shared<potEngine::SendMessageEventInfo>(4, _clientFd, _serverAddr, _playerId, potEngine::MOVE_LEFT, std::vector<uint16_t>{});
                        potEngine::eventBus.publish(moveInfo);
                    }
                    if (event->key == sf::Keyboard::D) {
                        auto moveInfo = std::make_shared<potEngine::SendMessageEventInfo>(4, _clientFd, _serverAddr, _playerId, potEngine::MOVE_RIGHT, std::vector<uint16_t>{});
                        potEngine::eventBus.publish(moveInfo);
                    }
                }
            }
        private:
            uint8_t _playerId;
            int _clientFd;
            struct sockaddr_in _serverAddr;
    };
};