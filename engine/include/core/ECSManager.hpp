#pragma once

#include <vector>
#include <memory>
#include <unordered_map>
#include <typeindex>
#include <algorithm>
#include "AEntity.hpp"
#include "ASystem.hpp"
#include "EventBus.hpp"
#include "StartEvent.hpp"
#include <SFML/Graphics.hpp>

#include <chrono>

namespace potEngine
{
        class Timer {
        public:
            Timer() {
                countTick = 60;
                previousTime = std::chrono::high_resolution_clock::now();
            }

            Timer(int counter) {
                countTick = counter;
                previousTime = std::chrono::high_resolution_clock::now();
            }

            ~Timer() {}

            void timerSetTimeNow() {
                previousTime = std::chrono::high_resolution_clock::now();
            }

            std::chrono::duration<double> timerGetElapsedTime() const {
                return std::chrono::high_resolution_clock::now() - previousTime;
            }

            void timerAddTick() {
                countTick += 1;
            }

            void timerSetTick(int counter) {
                countTick = counter;
            }

            int timerGetTick() const {
                return countTick;
            }

        private:
            int countTick = 0;
            std::chrono::time_point<std::chrono::high_resolution_clock> previousTime;
    };

    class ECSManager {
    public:
        ECSManager();
        ~ECSManager();

        std::shared_ptr<AEntity> createEntity();
        // std::shared_ptr<AEntity> createEntity(size_t Id);
        std::shared_ptr<AEntity> createServerEntity(size_t serverId);
        std::shared_ptr<AEntity> createWindowEntity();
        std::shared_ptr<AEntity> createSpriteEntity(const std::string &texturePath);

        static ECSManager& getInstance() {
            static ECSManager instance;
            return instance;
        }
        ECSManager(ECSManager const&) = delete;
        void operator=(ECSManager const&) = delete;

        // void addEntity(std::shared_ptr<AEntity> entity);
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

        void update(float deltaTime);
        void shutdown();

        std::vector<std::shared_ptr<AEntity>> getEntities() const;
        std::shared_ptr<AEntity> getEntity(size_t entity_id);
        // void setInput(sf::Keyboard::Key key, bool value) { _inputs[key] = value; };
        // bool getInput(sf::Keyboard::Key key) { return (_inputs[key]); };
        // std::unordered_map<sf::Keyboard::Key, bool> getInputs() { return (_inputs); };
        size_t getClientIdFromServerId(size_t serverId);
    private:
        std::size_t _entityCounter;
        std::unordered_map<size_t, size_t> _serverToClientId;

        std::vector<std::shared_ptr<ISystem>> _systems;
        std::vector<std::shared_ptr<AEntity>> _entities;
        // std::unordered_map<sf::Keyboard::Key, bool> _inputs;

    };

    template <typename T, typename...Args>
    void ECSManager::registerSystem(Args&&... args)
    {
        static_assert(std::is_base_of<ISystem, T>::value, "T must derive from ISystem");
        _systems.push_back(std::make_shared<T>(std::forward<Args>(args)...));
    }

    template <typename T>
    void ECSManager::unregisterSystem()
    {
        _systems.erase(std::remove_if(_systems.begin(), _systems.end(), [](const std::shared_ptr<ASystem>& system) {
            return typeid(T) == typeid(*system);
        }), _systems.end());
    }

    template <typename T>
    void ECSManager::addComponent(std::shared_ptr<AEntity> entity, std::shared_ptr<T> component) {
        entity->addComponent<T>(component);
        EntitySignatureChanged(entity);
    }
    static ECSManager& ecsManager = ECSManager::getInstance();
}