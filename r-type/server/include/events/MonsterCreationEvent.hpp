#pragma once

#include "server_config.hpp"


namespace potEngine
{
    class MonsterCreationInfo : public IEvent
    {
    public:
        std::size_t entity_id; // peut être, pas sur que ce soit utils
        std::size_t entity_type;
        int entity_hp;
        int entity_speed;
        std::vector<std::size_t> entity_pos;
        std::vector<std::size_t> entity_size;
        int entity_attack_pattern; // TODO - implementation avec le shoot
        int entity_move_pattern; 
                

        MonsterCreationInfo(std::size_t entityId)
            : entity_id(entityId) {}
    };

    class MonsterReadyToBeCreated : public IEvent
    {
    public:
        std::shared_ptr<potEngine::AEntity> info;

        MonsterReadyToBeCreated(std::shared_ptr<potEngine::AEntity> info)
            : info(info) {}
    };

    class MonsterCreationEvent : public IEvent
    {
    public:
        MonsterCreationEvent() {
            engine.subscribeEvent(this, &MonsterCreationEvent::monsterCreation);
        }
        ~MonsterCreationEvent() = default;

        void monsterCreation(std::shared_ptr<MonsterCreationInfo> info) {
            auto sendMessageToAllEventInfo = std::make_shared<SendMessageToAllEventInfo>(
                4,
                -1,
                info->entity_id,
                HURDLE,
                info->entity_pos, // TODO on rajoute quoi ?
                engine.getEntities()
            );
            engine.publishEvent(sendMessageToAllEventInfo);
        }
    };
}

// auto monster = engine.createEntity();
//            auto monsterComp = std::make_shared<MonsterComponent>(info->entity_hp);
//            auto posComp = std::make_shared<PositionComponent>(info->entity_pos[0], info->entity_pos[1]);
//            auto sizeComp = std::make_shared<SizeComponent>(info->entity_size[0], info->entity_size[1]);
//            auto moveComp = std::make_shared<MoveComponent>(info->entity_speed, info->entity_move_pattern);
//
//            engine.addComponent(monster, monsterComp);
//            engine.addComponent(monster, posComp);
//            engine.addComponent(monster, sizeComp);
//            engine.addComponent(monster, moveComp);
//
//            std::shared_ptr<MonsterReadyToBeCreated> ready = std::make_shared<MonsterReadyToBeCreated>(monster);
//            engine.publishEvent(ready);