#pragma once

#include "IEvent.hpp"
#include "EventBus.hpp"
#include "Engine.hpp"
#include "SendMessageToAllEvent.hpp"
#include "PlayerComponent.hpp"
#include "PositionComponent.hpp"
#include "MovementComponent.hpp"
#include "ShootComponent.hpp"
#include "MonstreComponent.hpp"

#include <netinet/in.h>
#include <vector>

namespace potEngine
{
    class EntityCreateInfoEvent : public IEvent {
    public:
        int max_players;
        int fd;
        std::vector<int> position;
        size_t entity_id; // de qui viens l'action si elle vient de quelqun
        EntityType entityType;

        EntityCreateInfoEvent(int maxP, int fd, std::vector<int> p, size_t entity_id, EntityType type)
            : max_players(maxP), fd(fd), position(p), entity_id(entity_id), entityType(type) {}
    };

    class EntityCreateEvent : public IEvent {
    public:
        EntityCreateEvent() {
            eventBus.subscribe(this, &EntityCreateEvent::EntityCreate);
        };

        void createShootEntity(std::shared_ptr<potEngine::AEntity> &entity, std::vector<int> pos)
        {
            std::shared_ptr<PositionComponent> positionComponent = std::make_shared<PositionComponent>(pos[0], pos[1]);
            std::shared_ptr<MovementComponent> movementComponent = std::make_shared<MovementComponent>(1.0f);
            std::shared_ptr<CollisionComponent> collisionComponent = std::make_shared<CollisionComponent>();
            std::shared_ptr<ShootComponent> shootComponent = std::make_shared<ShootComponent>();

            engine.addComponent(entity, positionComponent);
            engine.addComponent(entity, movementComponent);
            engine.addComponent(entity, collisionComponent);
            engine.addComponent(entity, shootComponent);
        }

        void createMonstreEntity(std::shared_ptr<potEngine::AEntity> &entity, std::vector<int> pos)
        {
            // TODO: ajouter les composants d'un monstre ici.
        }

        void EntityCreate(std::shared_ptr<EntityCreateInfoEvent> info)
        {
            auto entity = engine.createEntity();
            auto entity_id = entity->getID();

            std::vector<size_t> _pos;
            _pos.push_back(info->entityType);
            _pos.insert(_pos.end(), info->position.begin(), info->position.end());

            auto sendMessageToAllEventInfo = std::make_shared<SendMessageToAllExeptEventInfo>(
                info->max_players,
                info->fd,
                entity_id,
                INFORMATION,
                _pos,
                engine.getEntities()
            );
            eventBus.publish(sendMessageToAllEventInfo);

            if (info->entityType == EntityType::PEW)
                createShootEntity(entity, info->position);
            if (info->entityType == EntityType::MONSTRE)
                createMonstreEntity(entity, info->position);

            std::cout << "[SERVER] New entity created {ID}-[" << static_cast<int>(entity_id) << "] {TYPE}-[" << info->entityType << "]" << std::endl;
        }
    };
}
