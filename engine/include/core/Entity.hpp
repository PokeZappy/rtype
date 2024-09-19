#pragma once

#include <typeindex>
#include <unordered_map>
#include <optional>
#include <functional>
#include <memory>

namespace potEngine {
    class IComponent;
    class Entity {
    public:
        Entity(const std::size_t _id);
        ~Entity();

        template <typename T, typename... Args>
        void addComponent(Args&&... args);

        template <typename T>
        void removeComponent();

        template <typename T>
        std::optional<std::reference_wrapper<T>> getComponent();

        template <typename T>
        bool hasComponent() const;

        std::size_t getID() const;
    
    private:
        std::size_t _id;
        std::unordered_map<std::type_index, std::unique_ptr<IComponent>> _components;
    };
}