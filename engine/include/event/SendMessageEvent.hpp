#pragma once

#include "IEvent.hpp"
#include "EventBus.hpp"

#include <netinet/in.h>
#include <cmath>
#include <vector>

namespace potEngine
{
    class SendMessageEventInfo : public IEvent {
    public:
        int max_players;
        int socket;
        struct sockaddr_in client_addr;
        uint8_t entity_id;
        EventType event_type;
        std::vector<uint16_t> params;

        SendMessageEventInfo(int maxP, int socket, struct sockaddr_in addr, uint8_t id, EventType type, std::vector<uint16_t> p)
            : max_players(maxP), socket(socket), client_addr(addr), entity_id(id), event_type(type), params(p) {}
    };

    class SendMessageEvent : public IEvent {
    public:
        SendMessageEvent() {
            eventBus.subscribe(this, &SendMessageEvent::sendMessage);
        };

        void sendMessage(std::shared_ptr<SendMessageEventInfo> info) {
            // std::cout << "[CLIENT/SERVER][sendMessage] sending info..." << std::endl;
            send_message(info->client_addr, info->entity_id, info->event_type, info->params, info->max_players, info->socket);
        }
    private:
        void send_message(const struct sockaddr_in& addr, uint8_t entity_id, potEngine::EventType action, const std::vector<uint16_t>& params, int maxP, int socket)
        {
            int entity_id_bits = std::ceil(std::log2(maxP + 1));
            int action_bits = 8 - entity_id_bits;

            size_t packet_size = 1 + params.size() * sizeof(uint16_t);
            std::vector<uint8_t> packet(packet_size);

            packet[0] = (entity_id & ((1 << entity_id_bits) - 1)) << action_bits | (action & ((1 << action_bits) - 1));

            for (size_t i = 0; i < params.size(); ++i) {
                packet[1 + 2 * i] = (params[i] >> 8) & 0xFF;
                packet[1 + 2 * i + 1] = params[i] & 0xFF;
            }
            sendto(socket, packet.data(), packet.size(), 0, (const struct sockaddr*)&addr, sizeof(addr));
        }
    };
}
