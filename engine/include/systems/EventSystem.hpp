/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-cyprien.diederichs
** File description:
** EventSystem.hpp
*/


#include "ASystem.hpp"
#include "Entity.hpp"
#include "MovementSystem.hpp"

namespace potEngine
{
    class EventSystem : public ASystem {
    public:
        EventSystem() {}
        ~EventSystem() {}

        void handle_event(uint8_t client_id, uint8_t action, std::shared_ptr<Entity> player_entity, MovementSystem& movement_system)
        {
            switch (action) {
                case MOVE_UP:
                    movement_system.moveUp(player_entity);
                    break;
                case MOVE_DOWN:
                    movement_system.moveDown(player_entity);
                    break;
                case MOVE_LEFT:
                    movement_system.moveLeft(player_entity);
                    break;
                case MOVE_RIGHT:
                    movement_system.moveRight(player_entity);
                    break;
                default:
                    std::cerr << "Action inconnue reçue." << std::endl;
            }
        }
    };
}
