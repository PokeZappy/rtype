#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "ASystem.hpp"
#include "AEntity.hpp"
#include "WindowEntity.hpp"
#include "EventBus.hpp"
#include "WindowComponent.hpp"
#include "AudioComponent.hpp"
#include "MainLoopEvent.hpp"
#include "NoneEvent.hpp"

namespace potEngine {
    class AudioSystem : public ASystem {
    public:
        AudioSystem();
        ~AudioSystem();

        void update(float) override {};

        void updateSounds(std::shared_ptr<NoneEvent> event);
    };
}