#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "ECSManager.hpp"
#include "AEntity.hpp"
#include "RenderComponent.hpp"
#include "RenderSystem.hpp"
#include "WindowEntity.hpp"


namespace potEngine
{
    class gloop {
    public:
        gloop() = default;
        virtual ~gloop() = default;

        virtual int mainPotEngine();

    };
}

extern "C" potEngine::gloop* entry_point()
{
  return new potEngine::gloop;
}

extern "C" void delete_point(potEngine::gloop* gloop)
{
  delete gloop;
}