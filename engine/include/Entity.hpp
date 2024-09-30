/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-cyprien.diederichs
** File description:
** Entity.hpp
*/

#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <unordered_map>
#include <memory>
#include <string>
#include <typeinfo>

#include "IComponent.hpp"

namespace polEngine
{
    class Entity {
    public:
        int id;
        std::unordered_map<std::string, std::shared_ptr<IComponent>> components;

        Entity(int entityId) : id(entityId) {}

        template <typename T>
        void addComponent(std::shared_ptr<T> component) {
            components[typeid(T).name()] = component;
        }

        template <typename T>
        void removeComponent() {
            components.erase(typeid(T).name());
        }

        template <typename T>
        std::shared_ptr<T> getComponent() {
            auto it = components.find(typeid(T).name());
            if (it != components.end()) {
                return std::static_pointer_cast<T>(it->second);
            }
            return nullptr;
        }
    };
}

#endif // ENTITY_HPP
