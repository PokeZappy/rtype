#pragma once

#include <SFML/Graphics.hpp>
#include "ASystem.hpp"
#include "AEntity.hpp"
#include "WindowEntity.hpp"
#include "EventBus.hpp"
#include "ECSManager.hpp"
#include "WindowComponent.hpp"
#include <netinet/in.h>
#include "NoneEvent.hpp"
// #include "GameInclude.hpp" // TODO faire marcher cet include trop la flemme actuellement

namespace potEngine {
    class RecvMessageSystem : public ASystem {
    public:
        RecvMessageSystem(int cliFd, struct sockaddr_in servAddr, socklen_t adLen, size_t id);
        ~RecvMessageSystem();

        void handleCreateEntity(std::vector<size_t> params, size_t entity_id);
        static void createPlayerEntity(std::vector<size_t> params, size_t entity_id);
        void createShootEntity(std::vector<size_t> params, size_t entity_id);

        void update(float) override {};

        void updateSystem(std::shared_ptr<NoneEvent> event);
        std::tuple<size_t, potEngine::EventType, std::vector<size_t>> recv_message();
        int _clientFd;
        struct sockaddr_in _addr;
        socklen_t _addrLen;
        size_t _playerId;
    };
}