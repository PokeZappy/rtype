#include "AudioSystem.hpp"
#include "SpriteComponent.hpp"
#include "InputInfoEvent.hpp"
#include <iostream>

namespace potEngine {

    AudioSystem::AudioSystem() : ASystem()
    {
        _signature.set(AComponent::getID<AudioComponent>(), true);
        eventBus.subscribe(this, &AudioSystem::updateSounds);
    }

    AudioSystem::~AudioSystem() {

    }

    void AudioSystem::updateSounds(std::shared_ptr<BlcEvent> event) {
        for (auto entity : _entitiesSystem) {
           auto audioComponent = entity->getComponent<AudioComponent>();
           if (!audioComponent)
                continue;
            sf::Sound &sound = audioComponent->get()->getSound();
            bool isPlaying = audioComponent->get()->isPlaying();
            if (isPlaying && sound.getStatus() == sf::Sound::Stopped) {
                sound.play();
            }
            if (!isPlaying && sound.getStatus() == sf::Sound::Playing) {
                sound.stop();
            }
        }
    }
};