#include "RecvMessageSystem.hpp"
#include <iostream>
#include <cmath>
#include "PositionComponent.hpp"
#include "PlayerComponent.hpp"

namespace potEngine
{
    RecvMessageSystem::RecvMessageSystem(int cliFd, struct sockaddr_in servAddr, socklen_t adLen, uint8_t id) : _clientFd(cliFd), _addrLen(adLen), _playerId(id)
    {
        // _signature.set(AComponent::getID<RenderComponent>(), true);
        eventBus.subscribe(this, &RecvMessageSystem::updateSystem);
    }

    RecvMessageSystem::~RecvMessageSystem() {

    }

    std::tuple<uint8_t, potEngine::EventType, std::vector<uint16_t>> RecvMessageSystem::recv_message()
{
    uint8_t buffer[1024]; // TODO mettre BUFFER_SIZE macro
    ssize_t recv_len = recvfrom(_clientFd, buffer, sizeof(buffer), 0, (struct sockaddr*)&_addr, &_addrLen);

    if (recv_len < 0) {
        return std::make_tuple(0, potEngine::EventType::UNKNOW, std::vector<uint16_t>{});
    }

    int entity_id_bits = std::ceil(std::log2(4 + 1)); // TODO mettre macro MAX_PLAYERS
    int action_bits = 8 - entity_id_bits;

    uint8_t entity_id = (buffer[0] >> action_bits) & ((1 << entity_id_bits) - 1);
    uint8_t action = buffer[0] & ((1 << action_bits) - 1);

    potEngine::EventType event_type = static_cast<potEngine::EventType>(action);

    std::vector<uint16_t> params;
    for (ssize_t i = 1; i + 1 < recv_len; i += 2) {
        uint16_t param = (buffer[i] << 8) | buffer[i + 1];
        params.push_back(param);
    }

    return std::make_tuple(entity_id, event_type, params);
}

    void RecvMessageSystem::updateSystem(std::shared_ptr<BlcEvent> event) {
        // std::cout << "RECEIVE" << std::endl;
        auto [entity_id, event_type, params] = recv_message();
        if (event_type != potEngine::EventType::UNKNOW) {
            std::cout << "[CLIENT] Received event from server: " << static_cast<int>(event_type) << std::endl;
        }
        if (event_type == potEngine::EventType::CONNECTION) {
            std::cout << "[CLIENT] New entity created {ID}-[" << static_cast<int>(entity_id) << "]" << std::endl;
            ecsManager.createEntity(entity_id);
        }
        if (event_type == potEngine::EventType::DISCONNECT && entity_id == _playerId) {
            std::cout << "[CLIENT] Disconnected from server.\n";
            return;
        }
        if (event_type == potEngine::EventType::MOVE_UP || event_type == potEngine::EventType::MOVE_DOWN || event_type == potEngine::EventType::MOVE_LEFT || event_type == potEngine::EventType::MOVE_RIGHT) {
            auto entity = ecsManager.getEntity(entity_id);
            if (!entity) {
                std::cout << "[CLIENT] {ID}-[" << static_cast<int>(entity_id) << "] not found." << std::endl;
                return;
            }
            std::vector<int> convertedParams(params.begin(), params.end());
            entity->getComponent<potEngine::PositionComponent>()->get()->_position = convertedParams;
            std::cout << "[CLIENT] Entity {ID}-[" << std::to_string(static_cast<int>(entity_id))
                << "], {username}-[" << entity->getComponent<potEngine::PlayerComponent>()->get()->username << "], has move to {" << convertedParams[0] << "," << convertedParams[1] << "}" << std::endl;
        }
    }
}