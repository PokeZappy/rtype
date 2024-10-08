#pragma once

#include "IEvent.hpp"
#include "EventBus.hpp"
#include "AEntity.hpp"
#include "NetworkComponent.hpp"

#include <netinet/in.h>
#include <cmath>
#include <vector>
#include <cstring>

namespace potEngine
{
    class SendMessageToAllExeptEventInfo : public IEvent {
    public:
        int max_players;
        int fd;
        size_t entity_id;
        EventType event_type;
        std::vector<size_t> params;
        std::vector<std::shared_ptr<potEngine::AEntity>> entities;

        SendMessageToAllExeptEventInfo(int maxP, int fd, size_t id, EventType type, std::vector<size_t> p, std::vector<std::shared_ptr<potEngine::AEntity>> e)
            : max_players(maxP), fd(fd), entity_id(id), event_type(type), params(p), entities(e) {}
    };

    class SendMessageToAllExeptEvent : public IEvent {
    public:
        SendMessageToAllExeptEvent() {
            eventBus.subscribe(this, &SendMessageToAllExeptEvent::SendMessageToAllExept);
        };

        void SendMessageToAllExept(std::shared_ptr<SendMessageToAllExeptEventInfo> info)
        {
            if (ecsManager.getEntity(info->entity_id) == nullptr)
                return;
            send_message_to_all(info->entity_id, info->event_type, info->params, info->entities, info->max_players, info->fd);
        }
    private:
        void send_message(const struct sockaddr_in& addr, size_t entity_id, potEngine::EventType action, const std::vector<size_t>& params, size_t maxP, int fd)
        {
            const size_t EVENT_TYPE_BITS = 8;
            size_t packet_size = sizeof(size_t) + params.size() * sizeof(size_t);
            std::vector<uint8_t> packet(packet_size);

            size_t header = entity_id;
            header |= (static_cast<size_t>(action) << (sizeof(size_t) * 8 - EVENT_TYPE_BITS));
            std::memcpy(packet.data(), &header, sizeof(size_t));
            for (size_t i = 0; i < params.size(); ++i) {
                std::memcpy(packet.data() + sizeof(size_t) + i * sizeof(size_t), &params[i], sizeof(size_t));
            }
            sendto(fd, packet.data(), packet.size(), 0, (const struct sockaddr*)&addr, sizeof(addr));
        }


        void send_message_to_all(size_t entity_id, potEngine::EventType event_type, const std::vector<size_t>& params, const std::vector<std::shared_ptr<potEngine::AEntity>>& entities, int maxP, int fd)
        {
            for (const auto& entity : entities) {
                auto networkComponent = entity->getComponent<potEngine::NetworkComponent>();
                if (networkComponent && entity->getID() != entity_id) {
                    send_message(networkComponent->get()->addr, entity_id, event_type, params, maxP, networkComponent->get()->fd);
                }
            }
        }
    };
}
