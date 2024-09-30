#pragma once

#include "ASystem.hpp"
#include "WindowClearComponent.hpp"
#include "WindowEntity.hpp"

namespace potEngine {
    class WindowClearSystem : public ASystem {
    public:
        WindowClearSystem();
        ~WindowClearSystem();

        void update(float deltaTime, std::vector<std::shared_ptr<AEntity>> entities) override;
    };
}