#pragma once

#include <SFML/Graphics.hpp>
#include "ASystem.hpp"
#include "AEntity.hpp"
#include "WindowEntity.hpp"
#include "EventBus.hpp"
#include "ECSManager.hpp"
#include "WindowComponent.hpp"
#include "EventRender.hpp"
// #include "game_config.hpp" // TODO faire marcher cet include trop la flemme actuellement

namespace potEngine {
    class RecvMessageSystem : public ASystem {
    public:
        RecvMessageSystem();
        ~RecvMessageSystem();

        void update(float) override {};

        void updateSystem(std::shared_ptr<RecvMessageEventData> event);
        std::tuple<uint8_t, potEngine::EventType, std::vector<uint16_t>> recv_message(int clientFd, struct sockaddr_in& addr, socklen_t& addr_len);
    };
}