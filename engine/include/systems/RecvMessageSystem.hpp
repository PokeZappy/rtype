#pragma once

#include <SFML/Graphics.hpp>
#include "ASystem.hpp"
#include "AEntity.hpp"
#include "WindowEntity.hpp"
#include "EventBus.hpp"
#include "ECSManager.hpp"
#include "WindowComponent.hpp"
#include <netinet/in.h>
#include "BlcEvent.hpp"
// #include "game_config.hpp" // TODO faire marcher cet include trop la flemme actuellement

namespace potEngine {
    class RecvMessageSystem : public ASystem {
    public:
        RecvMessageSystem(int cliFd, struct sockaddr_in servAddr, socklen_t adLen, uint8_t id);
        ~RecvMessageSystem();

        void update(float) override {};

        void updateSystem(std::shared_ptr<BlcEvent> event);
        std::tuple<uint8_t, potEngine::EventType, std::vector<uint16_t>> recv_message();
        int _clientFd;
        struct sockaddr_in _addr;
        socklen_t _addrLen;
        uint8_t _playerId;
    };
}