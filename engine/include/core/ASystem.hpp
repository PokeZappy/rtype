#pragma once

#include "ISystem.hpp"

namespace potEngine {
    class ASystem : public ISystem {
    public:
        ASystem(bool inclusive = false);
        virtual ~ASystem() = default;

        virtual void update(float deltaTime) = 0;

        // void addEntity(AEntity& entity);
        // void removeEntity(const std::size_t id);

        std::vector<std::shared_ptr<AEntity>> &getEntities();
        std::bitset<64> getSignature() { return (_signature); }
        bool isInclusive() { return (_inclusive); }
    protected:
        std::vector<std::shared_ptr<AEntity>> _entitiesSystem;
        std::bitset<64> _signature;
        bool _inclusive; // permet de faire un système de signature inclusive : si set à true, il faut uniquement un composant pour que la signature match avec l'entity
    };
}