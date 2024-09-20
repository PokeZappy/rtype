//#include "ECSManager.hpp"
//
//#include <algorithm>
//
//namespace potEngine {
//
//    ECSManager::ECSManager(): _entityCounter() {}
//    ECSManager::~ECSManager() {}
//
//    Entity& ECSManager::createEntity()
//    {
//        _entities.emplace_back(_entityCounter++);
//        return _entities.back();
//    }
//
//    void ECSManager::removeEntity(const std::size_t id)
//    {
//        auto it = std::find_if(_entities.begin(), _entities.end(), [id](const Entity& entity) {
//            return entity.getID();
//        });
//
//        if (it != _entities.end()) {
//            _entities.erase(it);
//        }
//    }
//
//    template <typename T>
//    void ECSManager::registerSystem()
//    {
//        _systems[typeid(T)] = std::make_unique<T>();
//    }
//
//    template <typename T>
//    void ECSManager::unregisterSystem()
//    {
//        _systems.erase(typeid(T));
//    }
//
//    void ECSManager::init()
//    {
//        for (auto& system : _systems) {
//            system.second->init();
//        }
//    }
//
//    void ECSManager::update(float deltaTime)
//    {
//        for (auto& system : _systems) {
//            system.second->update(deltaTime);
//        }
//    }
//
//    void ECSManager::shutdown()
//    {
//        for (auto& system : _systems) {
//            system.second->shutdown();
//        }
//    }
//}