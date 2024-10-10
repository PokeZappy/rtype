#pragma once

#include "ClientCollisionInfoEvent.hpp"

namespace potEngine {
    class ClientCollisionEvent : public IEvent {
    public:
        ClientCollisionEvent() {
            eventBus.subscribe(this, &ClientCollisionEvent::handleClientCollision);
        };

        void handleClientCollision(std::shared_ptr<ClientCollisionInfoEvent> event) {
            auto entity1 = ecsManager.getEntity(event->collided_entity_id);
            auto entity2 = ecsManager.getEntity(event->colliding_entity_id);
            if (!entity1 || !entity2)
                return;
            if (entity1->getComponent<PlayerComponent>().has_value() && entity2->getComponent<ShootComponent>().has_value()) {
                ecsManager.removeEntity(entity2);
            }
            else if (entity1->getComponent<ShootComponent>().has_value() && entity2->getComponent<PlayerComponent>().has_value()) {
                ecsManager.removeEntity(entity1);
            }
        }
    };
}