#pragma once

#include "IEvent.hpp"
#include "EventBus.hpp"
#include "ECSManager.hpp"
#include "SendMessageToAllEvent.hpp"
#include "PlayerComponent.hpp"
#include "PositionComponent.hpp"
#include "LifeComponent.hpp"

#include <netinet/in.h>
#include <vector>

namespace potEngine
{
    class CollisionInfoEvent : public IEvent {
    public:
        int max_players;
        int player_fd;
        size_t colliding_entity_id; // l'ID de l'entité qui entre en collision avec une autre
        size_t collided_entity_id; // l'ID de l'entité qui subit la collision

        CollisionInfoEvent(int maxP, int player_fd,  size_t colliding_entity_id, size_t collided_entity_id)
            : max_players(maxP), player_fd(player_fd), colliding_entity_id(colliding_entity_id), collided_entity_id(collided_entity_id) {}
    };

    class CollisionEvent : public IEvent {
    public:
        CollisionEvent() {
            eventBus.subscribe(this, &CollisionEvent::Collision);
        };

        void collision_lifeEntity_shoot(std::shared_ptr<potEngine::AEntity> lifeEntity, std::shared_ptr<potEngine::AEntity> shoot, std::shared_ptr<CollisionInfoEvent> info)
        {
            auto username = lifeEntity->getComponent<PlayerComponent>()->get()->username;
            auto life = lifeEntity->getComponent<LifeComponent>()->get()->life - 1;

            auto sendCollisionMsgToAll = std::make_shared<SendMessageToAllEventInfo>(
                info->max_players,
                info->player_fd,
                lifeEntity->getID(),
                COLLISION,
                std::vector<size_t> {shoot->getID()},
                ecsManager.getEntities()
            );
            eventBus.publish(sendCollisionMsgToAll);

            ecsManager.removeEntity(shoot->getID());
            std::cout << "[SERVER] Player {ID}-[" << lifeEntity->getID() << "], {username}-["
                << username << "] collide and has now {LIFE}-[" << life << "]" << std::endl;

            if (life <= 0) {
                auto sendMessageToAllEventInfo = std::make_shared<SendMessageToAllEventInfo>(
                    info->max_players,
                    info->player_fd,
                    lifeEntity->getID(),
                    DEATH,
                    std::vector<size_t>{},
                    ecsManager.getEntities()
                );
                eventBus.publish(sendMessageToAllEventInfo);
                ecsManager.removeEntity(lifeEntity->getID());
                std::cout << "[SERVER] Player {ID}-[" << lifeEntity->getID() << "], {username}-["
                    << username << "] is dead." << std::endl;
            }
            lifeEntity->getComponent<LifeComponent>()->get()->life--;
        }

        void collision_player_monstre(std::shared_ptr<potEngine::AEntity> player, std::shared_ptr<potEngine::AEntity> monstre)
        {
            // TODO: faire la collision entre monstre et joueur ici.
        }

        void Collision(std::shared_ptr<CollisionInfoEvent> info)
        {
            auto colliding_entity = ecsManager.getEntity(info->colliding_entity_id);
            auto collided_entity = ecsManager.getEntity(info->collided_entity_id);
            if (colliding_entity == nullptr || collided_entity == nullptr) {
                std::cout << "[SERVER][COLLISION] At least one entity do not exist." << std::endl;
                return;
            }

            if (colliding_entity->getComponent<ShootComponent>()) {
                if (collided_entity->getComponent<PlayerComponent>() || collided_entity->getComponent<MonstreComponent>())
                    collision_lifeEntity_shoot(collided_entity, colliding_entity, info);
            }

            if (colliding_entity->getComponent<PlayerComponent>() || colliding_entity->getComponent<MonstreComponent>()) {
                if (collided_entity->getComponent<ShootComponent>())
                    collision_lifeEntity_shoot(colliding_entity, collided_entity, info);
            }
        }
    };
}
