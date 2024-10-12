#pragma once

#include "ClientCollisionInfoEvent.hpp"

namespace potEngine {
    class ClientCollisionEvent : public IEvent {
    public:
        ClientCollisionEvent() {
            engine.subscribeEvent(this, &ClientCollisionEvent::handleClientCollision);
        };

        void handleClientCollision(std::shared_ptr<ClientCollisionInfoEvent> event) {
            auto entity1 = engine.getEntity(event->collided_entity_id);
            auto entity2 = engine.getEntity(event->colliding_entity_id);
            if (!entity1 || !entity2)
                return;
            if (entity1->getComponent<PlayerComponent>().has_value() && entity2->getComponent<ShootComponent>().has_value()) {
                engine.removeEntity(entity2);
            }
            else if (entity1->getComponent<ShootComponent>().has_value() && entity2->getComponent<PlayerComponent>().has_value()) {
                engine.removeEntity(entity1);
            }
        }
    };
}