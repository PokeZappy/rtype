#pragma once

#include "AComponent.hpp"

namespace potEngine
{
    class MonstreComponent : public AComponent {
    public:
        MonstreComponent(int nbMonster) : monsterId(nbMonster);
        ~MonstreComponent() = default;
        int monsterId;
    };
}
