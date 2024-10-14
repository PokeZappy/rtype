#pragma once

#include <vector>
#include <memory>
#include <unordered_map>
#include <typeindex>
#include <algorithm>
#include <chrono>

#include <SFML/Graphics.hpp>

#include "AEntity.hpp"
#include "ASystem.hpp"
#include "EventBus.hpp"
#include "StartEvent.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <chrono>

namespace potEngine
{
    class Timer {
    public:
        double fdp;

        Timer() : _countTick(0), _firstCall(true) {}

        ~Timer() {}

        void timerAddTick() {
            _countTick += 1;
        }

        void timerSetTick(int counter) {
            _countTick = counter;
        }

        int timerGetTick() const {
            return _countTick;
        }

        void setTps(int number) {
            _tps = number;
        }

        int timerGetTps() const {
            return _tps;
        }

        void initializePreviousTime() {
            _previousTime = std::chrono::high_resolution_clock::now();
            _firstCall = false;
        }

        double getPreviousTime() {
            auto now = std::chrono::high_resolution_clock::now();
            auto duration = now - _previousTime;
            return std::chrono::duration<double>(duration).count();
        }

        std::chrono::duration<double> getElapsedTimeSinceLastTick() {
            auto now = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = now - _previousTime;
            _previousTime = now;
            return elapsed;
        }

        double getTickDuration() {
            return 1.0f / _tps;
        }

        bool isFirstCall() const {
            return _firstCall;
        }

    private:
        int _tps = 0;
        int _countTick = 0;
        bool _firstCall;
        std::chrono::time_point<std::chrono::high_resolution_clock> _previousTime;
    };


    class Engine {
    public:
        Timer timer;

        Engine();
        ~Engine();

        std::shared_ptr<AEntity> createEntity();
        std::shared_ptr<AEntity> createServerEntity(size_t serverId);
        std::shared_ptr<AEntity> createWindowEntity();
        std::shared_ptr<AEntity> createSpriteEntity(const std::string &texturePath);

        static Engine& getInstance() {
            static Engine instance;
            return instance;
        }
        Engine(Engine const&) = delete;
        void operator=(Engine const&) = delete;

        template <typename T>
        void addComponent(std::shared_ptr<AEntity> entity, std::shared_ptr<T> component);

        void removeEntity(const std::size_t id);
        void removeEntity(std::shared_ptr<AEntity> entity);

        template <typename T, typename... Args>
        void registerSystem(Args&&... args);
        template <typename T>
        void unregisterSystem();

        void EntitySignatureChanged(std::shared_ptr<AEntity> entity);
        void EraseEntitySystem(std::shared_ptr<AEntity> entity);

        void update();
        void shutdown();

        std::vector<std::shared_ptr<AEntity>> getEntities() const;
        std::shared_ptr<AEntity> getEntity(size_t entity_id);
        size_t getClientIdFromServerId(size_t serverId);

        template<class T, class EventType>
        void subscribeEvent(T* instance, void (T::*memberFunction)(std::shared_ptr<EventType>)) {
            _eventBus.subscribe(instance, memberFunction);
        }

        template<class EventType>
        void publishEvent(std::shared_ptr<EventType> event) {
            _eventBus.publish(event);
        }
        void setTick(int _tps);
    private:
        std::size_t _entityCounter;
        std::unordered_map<size_t, size_t> _serverToClientId;

        std::vector<std::shared_ptr<ISystem>> _systems;
        std::vector<std::shared_ptr<AEntity>> _entities;
        EventBus& _eventBus = EventBus::getInstance();
        // std::unordered_map<sf::Keyboard::Key, bool> _inputs;

    };

    template <typename T, typename...Args>
    void Engine::registerSystem(Args&&... args)
    {
        static_assert(std::is_base_of<ISystem, T>::value, "T must derive from ISystem");
        _systems.push_back(std::make_shared<T>(std::forward<Args>(args)...));
    }

    template <typename T>
    void Engine::unregisterSystem()
    {
        _systems.erase(std::remove_if(_systems.begin(), _systems.end(), [](const std::shared_ptr<ASystem>& system) {
            return typeid(T) == typeid(*system);
        }), _systems.end());
    }

    template <typename T>
    void Engine::addComponent(std::shared_ptr<AEntity> entity, std::shared_ptr<T> component) {
        entity->addComponent<T>(component);
        EntitySignatureChanged(entity);
    }
    static Engine& engine = Engine::getInstance();
}