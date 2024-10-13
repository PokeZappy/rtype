#include "AudioSystem.hpp"
#include "SpriteComponent.hpp"
#include "InputInfoEvent.hpp"

namespace potEngine {

    AudioSystem::AudioSystem() : ASystem()
    {
        _signature.set(AComponent::getID<AudioComponent>(), true);
        engine.subscribeEvent(this, &AudioSystem::updateSounds);
    }

    AudioSystem::~AudioSystem() {

    }

    void AudioSystem::updateSounds(std::shared_ptr<NoneEvent> event) {
        for (auto entity : _entitiesSystem) {
           auto audioComponent = entity->getComponent<AudioComponent>();
           if (!audioComponent)
                continue;
            sf::Sound &sound = audioComponent->get()->getSound();
            bool hasPlayedOnce = audioComponent->get()->getHasPlayedOnce();
            bool isLooping = audioComponent->get()->isOnLoop();
            bool isPlaying = audioComponent->get()->isPlaying();

            if (sound.getStatus() == sf::Sound::Stopped && !isLooping && hasPlayedOnce) {
                engine.removeComponent<AudioComponent>(entity);
                continue;
            }
            if (isPlaying && sound.getStatus() == sf::Sound::Stopped) {
                audioComponent->get()->hasPlayedOnce(true);
                sound.play();
            }
            if (!isPlaying && sound.getStatus() == sf::Sound::Playing) {
                sound.stop();
            }
        }
    }
};