#pragma once

#include "IEvent.hpp"
#include "EventBus.hpp"
#include "AEntity.hpp"
#include "NetworkComponent.hpp"

#include "cross_config.hpp"
#include <cmath>
#include <vector>

namespace potEngine
{
    class SendMessageToAllExeptEventInfo : public IEvent {
    public:
        int max_players;
        int socket;
        uint8_t entity_id;
        EventType event_type;
        std::vector<uint16_t> params;
        std::vector<std::shared_ptr<potEngine::AEntity>> entities;

        SendMessageToAllExeptEventInfo(int maxP, int socket, uint8_t id, EventType type, std::vector<uint16_t> p, std::vector<std::shared_ptr<potEngine::AEntity>> e)
            : max_players(maxP), socket(socket), entity_id(id), event_type(type), params(p), entities(e) {}
    };

    class SendMessageToAllExeptEvent : public IEvent {
    public:
        SendMessageToAllExeptEvent() {
            eventBus.subscribe(this, &SendMessageToAllExeptEvent::SendMessageToAllExept);
        };

        void SendMessageToAllExept(std::shared_ptr<SendMessageToAllExeptEventInfo> info) {
            std::cout << "[CLIENT/SERVER][sendMessage] sending info to all..." << std::endl;
            send_message_to_all(info->entity_id, info->event_type, info->params, info->entities, info->max_players, info->socket);
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

        void send_message_to_all(uint8_t entity_id, potEngine::EventType event_type, const std::vector<uint16_t>& params, const std::vector<std::shared_ptr<potEngine::AEntity>>& entities, int maxP, int socket)
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
