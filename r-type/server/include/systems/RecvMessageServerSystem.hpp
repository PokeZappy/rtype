/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-cyprien.diederichs
** File description:
** RecvMessageServerSystem.hpp
*/

#pragma once

#include <cstring>

#include "ASystem.hpp"
#include "AEntity.hpp"
#include "EventBus.hpp"
#include "ECSManager.hpp"
#include "NoneEvent.hpp"
#include "ConnectionEvent.hpp"
#include "DisconnectionEvent.hpp"
#include "MoveEvent.hpp"
#include "EntityCreateEvent.hpp"
#include "Config.hpp"


namespace potEngine
{
    class RecvMessageServerSystem : public ASystem {
    public:
        int _serverFd;
        struct sockaddr_in _addr;
        socklen_t _addrLen;
        int current_players;

        void update(float) override {};

        RecvMessageServerSystem(int serverFd, struct sockaddr_in server_addr, socklen_t server_addr_len)
            : _serverFd(serverFd), _addr(server_addr), _addrLen(server_addr_len), current_players(0)
        {
            eventBus.subscribe(this, &RecvMessageServerSystem::updateSystem);
        }

        ~RecvMessageServerSystem() {}

        std::tuple<size_t, EventType, std::vector<size_t>> recv_message()
        {
            uint8_t buffer[BUFFER_SIZE];
            ssize_t recv_len = RECVFROM(_serverFd, buffer, sizeof(buffer), 0, (struct sockaddr*)&_addr, &_addrLen);

            if (recv_len < 0 || static_cast<size_t>(recv_len) < sizeof(size_t)) {
                return std::make_tuple(0, EventType::UNKNOW, std::vector<size_t>{});
            }

            size_t header;
            std::memcpy(&header, buffer, sizeof(size_t));
            size_t entity_id = header & ((1ULL << (sizeof(size_t) * 8 - 8)) - 1);
            EventType event_type = static_cast<EventType>(header >> (sizeof(size_t) * 8 - 8));
            std::vector<size_t> params;
            for (size_t i = sizeof(size_t); i + sizeof(size_t) <= static_cast<size_t>(recv_len); i += sizeof(size_t)) {
                size_t param;
                std::memcpy(&param, buffer + i, sizeof(size_t));
                params.push_back(param);
            }
            return std::make_tuple(entity_id, event_type, params);
        }

        void updateSystem(std::shared_ptr<NoneEvent> event)
        {
            auto [entity_id, event_type, params] = recv_message();
            // if (event_type != EventType::UNKNOW)
            //     std::cout << "[SERVER] Received event from client: " << static_cast<int>(event_type) << std::endl;

            if (event_type == CONNECTION && 4 > current_players) {
                auto connectionInfo = std::make_shared<ConnectionInfoEvent>(4, _serverFd, _addr, params);
                eventBus.publish(connectionInfo);
                current_players++;
            }
            if (event_type == DISCONNECT) {
                auto disconnectInfo = std::make_shared<DisconnectionInfoEvent>(4, _serverFd, entity_id, params);
                eventBus.publish(disconnectInfo);
                current_players--;
            }
            if (event_type == MOVE_UP || event_type == MOVE_DOWN || event_type == MOVE_RIGHT || event_type == MOVE_LEFT) {
                auto moveInfo = std::make_shared<MoveInfoEvent>(4, _serverFd, event_type, entity_id);
                eventBus.publish(moveInfo);
            }
            if (event_type == SHOOT) {
                auto createShootEntity = std::make_shared<EntityCreateInfoEvent>(
                    4,
                    _serverFd,
                    ecsManager.getEntity(entity_id)->getComponent<PositionComponent>()->get()->_position,
                    entity_id,
                    EntityType::PEW
                );
                eventBus.publish(createShootEntity);
            } if (event_type == DEATH) {
                std::cout << "[SERVER] Entity {ID}-[" << entity_id << "] is removed." << std::endl;
                ecsManager.removeEntity(entity_id);
            }
        }
    };
}