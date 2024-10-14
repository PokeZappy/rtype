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
            if (entity == nullptr) {
                std::cout << "l'entité n'existe pas c'est pas normal mon reuf" << std::endl;
            }
           auto audioComponent = entity->getComponent<AudioComponent>();
           if (audioComponent == std::nullopt)
                continue;
            sf::Sound &sound = audioComponent->get()->getSound();
            bool hasPlayedOnce = audioComponent->get()->getHasPlayedOnce();
            bool isLooping = audioComponent->get()->isOnLoop();
            bool isPlaying = audioComponent->get()->isPlaying();

            if (sound.getStatus() == sf::Sound::Stopped && !isLooping && hasPlayedOnce) {
                toRemove.push_back(entity);
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
        for (auto audio : toRemove) {
            engine.removeComponent<AudioComponent>(audio);
        }
        toRemove.clear();
    }
};