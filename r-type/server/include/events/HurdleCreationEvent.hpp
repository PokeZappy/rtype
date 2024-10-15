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

        HurdleCreationInfo(std::size_t entityId)
            : entity_id(entityId) {}
    };

    class HurdleReadyToBeCreated : public IEvent
    {
    public:
        std::shared_ptr<potEngine::AEntity> info;

        HurdleReadyToBeCreated(std::shared_ptr<potEngine::AEntity> info)
            : info(info) {}
    };

    class HurldeCreationEvent : public IEvent
    {
    public:
        HurdleCreationEvent() = default;
        ~HurdleCreationEvent() = default;

        void HurdleCreation(std::shared_ptr<HurdleCreationInfo> info)
        {
            auto hurdle = engine.createEntity();
            auto HurdleComp = std::make_shared<HurdleComponent>(info->entity_hp);
            auto posComp = std::make_shared<PositionComponent>(info->entity_pos[0], info->entity_pos[1]);
            auto sizeComp = std::make_shared<SizeComponent>(info->entity_size[0], info->entity_size[1]);

            engine.addComponent(hurdle, HurdleComp);
            engine.addComponent(hurdle, posComp);
            engine.addComponent(hurdle, sizeComp);

            std::shared_ptr<HurdleReadyToBeCreated> ready = std::make_shared<HurdleReadyToBeCreated>(hurdle);
            engine.publishEvent(ready);
        }
    };
}