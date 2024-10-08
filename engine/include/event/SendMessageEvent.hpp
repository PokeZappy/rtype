#pragma once

#include "IEvent.hpp"
#include "EventBus.hpp"

#include <netinet/in.h>
#include <cmath>
#include <vector>
#include <cstring>

namespace potEngine
{
    class SendMessageEventInfo : public IEvent {
    public:
        int max_players;
        int fd;
        struct sockaddr_in client_addr;
        size_t entity_id;
        EventType event_type;
        std::vector<size_t> params;

        SendMessageEventInfo(int maxP, int fd, struct sockaddr_in addr, size_t id, EventType type, std::vector<size_t> p)
            : max_players(maxP), fd(fd), client_addr(addr), entity_id(id), event_type(type), params(p) {}
    };

    class SendMessageEvent : public IEvent {
    public:
        SendMessageEvent() {
            eventBus.subscribe(this, &SendMessageEvent::sendMessage);
        };

        void sendMessage(std::shared_ptr<SendMessageEventInfo> info)
        {
            if (info->entity_id != 0 && ecsManager.getEntity(info->entity_id) == nullptr)
                return;
            send_message(info->client_addr, info->entity_id, info->event_type, info->params, info->max_players, info->fd);
        }
    private:
        void send_message(const struct sockaddr_in& addr, size_t entity_id, potEngine::EventType action, const std::vector<size_t>& params, size_t maxP, int fd)
        {
            int entity_id_bits = std::ceil(std::log2(maxP + 1));
            int action_bits = sizeof(size_t) * 8 - entity_id_bits;

            size_t packet_size = sizeof(size_t) + params.size() * sizeof(size_t);
            std::vector<uint8_t> packet(packet_size);
            size_t header = (entity_id & ((1 << entity_id_bits) - 1)) << action_bits | (action & ((1 << action_bits) - 1));
            std::memcpy(packet.data(), &header, sizeof(size_t));
            for (size_t i = 0; i < params.size(); ++i) {
                std::memcpy(packet.data() + sizeof(size_t) + i * sizeof(size_t), &params[i], sizeof(size_t));
            }
            sendto(fd, packet.data(), packet.size(), 0, (const struct sockaddr*)&addr, sizeof(addr));
        }
    };
}
