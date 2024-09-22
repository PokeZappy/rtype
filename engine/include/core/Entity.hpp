#pragma once

#include <typeindex>
#include <unordered_map>
#include <optional>
#include <functional>
#include <memory>

#include "IComponent.hpp"

namespace potEngine {
    class IComponent;
    class Entity {
    public:
        Entity(const std::size_t _id);
        ~Entity();

        template <typename T>
        void addComponent(std::shared_ptr<T> component);

        template <typename T>
        void removeComponent();

        template <typename T>
        std::optional<std::shared_ptr<T>> getComponent();

        template <typename T>
        bool hasComponent() const;

        std::size_t getID() const;

    private:
        std::size_t _id;
        std::unordered_map<std::type_index, std::shared_ptr<IComponent>> _components;
    };

    template <typename T>
    void Entity::addComponent(std::shared_ptr<T> component)
    {
        _components[typeid(T)] = component;
    }

    template <typename T>
    void Entity::removeComponent()
    {
        _components.erase(typeid(T));
    }

    template <typename T>
    std::optional<std::shared_ptr<T>> Entity::getComponent() {
        auto it = _components.find(typeid(T));
        if (it != _components.end()) {
            auto component = std::dynamic_pointer_cast<T>(it->second);
            if (component) {
                return component;
            }
        }
        return std::nullopt;
    }

    template <typename T>
    bool Entity::hasComponent() const
    {
        return _components.find(typeid(T)) != _components.end();
    }
}
