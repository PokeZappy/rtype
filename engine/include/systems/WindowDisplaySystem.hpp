#pragma once

#include "ASystem.hpp"
#include "WindowDisplayComponent.hpp"
#include "WindowEntity.hpp"

namespace potEngine {
    class WindowDisplaySystem : public ASystem {
    public:
        WindowDisplaySystem();
        ~WindowDisplaySystem();

        void update(float deltaTime, std::vector<std::shared_ptr<Entity>> entities) override;
    };
}