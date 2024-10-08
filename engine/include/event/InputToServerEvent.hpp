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
            InputToServerEvent(size_t playerId, int clientFd, struct sockaddr_in serverAddr) : _playerId(playerId), _clientFd(clientFd), _serverAddr(serverAddr) {
                eventBus.subscribe(this, &InputToServerEvent::handleInputs);
            };
            void handleInputs(std::shared_ptr<InputInfoEvent> event) {
                if (event->type == sf::Event::KeyPressed) {
                    if (event->key == sf::Keyboard::X) {
                        auto disconnectEventInfo = std::make_shared<potEngine::SendMessageEventInfo>(MAX_PLAYERS, _clientFd, _serverAddr, _playerId, potEngine::DISCONNECT, std::vector<size_t>{});
                        potEngine::eventBus.publish(disconnectEventInfo);
                    }
                    if (event->key == sf::Keyboard::Z) {
                        auto moveInfo = std::make_shared<potEngine::SendMessageEventInfo>(MAX_PLAYERS, _clientFd, _serverAddr, _playerId, potEngine::MOVE_UP, std::vector<size_t>{});
                        potEngine::eventBus.publish(moveInfo);
                    }
                    if (event->key == sf::Keyboard::S) {
                        auto moveInfo = std::make_shared<potEngine::SendMessageEventInfo>(MAX_PLAYERS, _clientFd, _serverAddr, _playerId, potEngine::MOVE_DOWN, std::vector<size_t>{});
                        potEngine::eventBus.publish(moveInfo);
                    }
                    if (event->key == sf::Keyboard::Q) {
                        auto moveInfo = std::make_shared<potEngine::SendMessageEventInfo>(MAX_PLAYERS, _clientFd, _serverAddr, _playerId, potEngine::MOVE_LEFT, std::vector<size_t>{});
                        potEngine::eventBus.publish(moveInfo);
                    }
                    if (event->key == sf::Keyboard::D) {
                        auto moveInfo = std::make_shared<potEngine::SendMessageEventInfo>(MAX_PLAYERS, _clientFd, _serverAddr, _playerId, potEngine::MOVE_RIGHT, std::vector<size_t>{});
                        potEngine::eventBus.publish(moveInfo);
                    }
                    if (event->key == sf::Keyboard::G) {
                        auto moveInfo = std::make_shared<potEngine::SendMessageEventInfo>(MAX_PLAYERS, _clientFd, _serverAddr, _playerId, potEngine::SHOOT, std::vector<size_t>{});
                        potEngine::eventBus.publish(moveInfo);
                    }
                }
            }
        private:
            size_t _playerId;
            int _clientFd;
            struct sockaddr_in _serverAddr;
    };
};