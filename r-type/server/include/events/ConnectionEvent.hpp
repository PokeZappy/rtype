#pragma once

#include <vector>

#include "IEvent.hpp"
#include "EventBus.hpp"
#include "Engine.hpp"
#include "SendMessageToAllExeptEvent.hpp"
#include "SendAllDataEvent.hpp"
#include "PlayerComponent.hpp"
#include "PositionComponent.hpp"
#include "MovementComponent.hpp"
#include "Config.hpp"

namespace potEngine
{
    class ConnectionInfoEvent : public IEvent {
    public:
        int max_players;
        int fd;
        struct sockaddr_in client_addr;
        std::vector<size_t> params;

        ConnectionInfoEvent(int maxP, int fd, struct sockaddr_in c_addr, std::vector<size_t> p)
            : max_players(maxP), fd(fd), client_addr(c_addr), params(p) {}
    };

    class ConnectionEvent : public IEvent {
    public:
        ConnectionEvent() {
            engine.subscribeEvent(this, &ConnectionEvent::connect);
        };

        void connect(std::shared_ptr<ConnectionInfoEvent> info) {
            auto player_entity = engine.createEntity();
            size_t player_id = player_entity->getID();
            std::string player_name;

            if (info->params.empty()) {
                player_name = "Player_" + std::to_string(static_cast<int>(player_id));
            } else {
                player_name.assign(info->params.begin(), info->params.end());
            }

            std::shared_ptr<PlayerComponent> playerComponent = std::make_shared<PlayerComponent>(player_name);
            std::shared_ptr<PositionComponent> positionComponent = std::make_shared<PositionComponent>(0.0f, 0.0f);
            std::shared_ptr<MovementComponent> movementComponent = std::make_shared<MovementComponent>(5.0f);
            std::shared_ptr<NetworkComponent> networkComponent = std::make_shared<NetworkComponent>(info->client_addr, info->fd);
            std::shared_ptr<LifeComponent> lifeComponent = std::make_shared<LifeComponent>(3);
            std::shared_ptr<CollisionComponent> collisionComponent = std::make_shared<CollisionComponent>();

            engine.addComponent(player_entity, playerComponent);
            engine.addComponent(player_entity, positionComponent);
            engine.addComponent(player_entity, movementComponent);
            engine.addComponent(player_entity, networkComponent);
            engine.addComponent(player_entity, lifeComponent);
            engine.addComponent(player_entity, collisionComponent);

            std::cout << "[SERVER] Player connected: {id}-[" << std::to_string(static_cast<int>(player_id))
                << "], {username}-[" << player_name << "]" << "params : " ;
            if (!info->params.empty())
                for (auto para: info->params)
                    std::cout << para << " ";
            std::cout << std::endl;

            auto sendMessageEventInfo = std::make_shared<SendMessageEventInfo>(info->max_players, info->fd, info->client_addr, player_id, CONNECTION, info->params);
            engine.publishEvent(sendMessageEventInfo);

            std::vector<int> position = {0, 0};
            std::vector<size_t> _pos;
            _pos.push_back(EntityType::PLAYER);
            _pos.push_back(static_cast<size_t>(player_name.size()));
            for (char c : player_name) {
                _pos.push_back(static_cast<size_t>(c));
            }
            _pos.insert(_pos.end(), position.begin(), position.end());
            auto sendMessageToAllEventInfo = std::make_shared<SendMessageToAllExeptEventInfo>(info->max_players, info->fd, player_id, CONNECTION, _pos, engine.getEntities());
            engine.publishEvent(sendMessageToAllEventInfo);

            auto sendDataEventInfo = std::make_shared<SendAllDataInfoEvent>(
                info->max_players,
                info->fd,
                info->client_addr,
                player_id
            );
            engine.publishEvent(sendDataEventInfo);
        }
    };
}
