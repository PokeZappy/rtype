#pragma once

#include "server_config.hpp"


namespace potEngine
{
    class HurdleCreationInfo : public IEvent
    {
    public:
        std::size_t entity_id; // peut être, pas sur que ce soit utils
        std::size_t entity_type;
        std::vector<std::size_t> entity_pos;
        std::vector<std::size_t> entity_size;
        std::vector<std::size_t> hitbox;
        sf::Vector2f final_pos;
        HurdleCreationInfo(std::size_t entityId, std::vector<std::size_t> enityPos)
            : entity_id(entityId), entity_pos(enityPos) {}
    };

    class HurdleReadyToBeCreated : public IEvent
    {
    public:
        std::shared_ptr<potEngine::AEntity> info;

        HurdleReadyToBeCreated(std::shared_ptr<potEngine::AEntity> info)
            : info(info) {}
    };

    class HurdleCreationEvent : public IEvent
    {
    public:
        HurdleCreationEvent() {
            engine.subscribeEvent(this, &HurdleCreationEvent::HurdleCreation);
        };
        ~HurdleCreationEvent() = default;

        void HurdleCreation(std::shared_ptr<HurdleCreationInfo> info)
        {
                auto sendMessageToAllEventInfo = std::make_shared<SendMessageToAllEventInfo>(
                4,
                -1,
                info->entity_id,
                HURDLE,
                info->entity_pos,
                engine.getEntities()
            );
            engine.publishEvent(sendMessageToAllEventInfo);
//            auto hurdle = engine.createEntity();
//            auto hurdleComp = std::make_shared<HurdleComponent>(info->entity_hp);
//            auto posComp = std::make_shared<PositionComponent>(info->entity_pos[0], info->entity_pos[1]);
//            auto sizeComp = std::make_shared<SizeComponent>(info->entity_size[0], info->entity_size[1]);
//            auto staticMouv = std::make_shared<staticMoveComponent>(info->entity_pos, info->final_pos);
//
//            engine.addComponent(hurdle, hurdleComp);
//            engine.addComponent(hurdle, posComp);
//            engine.addComponent(hurdle, sizeComp);
//            engine.addComponent(hurdle, staticMouv);
//
//            std::shared_ptr<HurdleReadyToBeCreated> ready = std::make_shared<HurdleReadyToBeCreated>(hurdle);
//            engine.publishEvent(ready);
        }
    };
}