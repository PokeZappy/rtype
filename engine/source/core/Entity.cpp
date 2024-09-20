//#include "Entity.hpp"
//
//namespace potEngine
//{
//    Entity::Entity(const std::size_t id): _id(id) {}
//
//    Entity::~Entity()
//    {
//        _components.clear();
//    }
//
//    template <typename T, typename... Args>
//    void Entity::addComponent(Args&&... args)
//    {
//        _components[typeid(T)] = std::make_unique<T>(std::forward<Args>(args)...);
//    }
//
//    template <typename T>
//    void Entity::removeComponent()
//    {
//        _components.erase(typeid(T));
//    }
//
//    template <typename T>
//    std::optional<std::reference_wrapper<T>> Entity::getComponent()
//    {
//        auto it = _components.find(typeid(T));
//        T* component;
//
//        if (it != _components.end())
//        {
//            component = dynamic_cast<T*>(it->second.get());
//            if (component) {
//                return std::ref(*component);
//            }
//        }
//        return std::nullopt;
//    }
//
//    template <typename T>
//    bool Entity::hasComponent() const
//    {
//        return _components.find(typeid(T)) != _components.end();
//    }
//
//    std::size_t Entity::getID() const
//    {
//        return _id;
//    }
//}
