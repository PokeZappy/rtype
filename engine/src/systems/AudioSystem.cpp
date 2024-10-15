#include "AudioSystem.hpp"
#include "SpriteComponent.hpp"
#include "InputInfoEvent.hpp"
#include <iostream>

namespace potEngine {

    /*!
    * @brief Construct a new Audio System object.
    *
    * This constructor initializes the AudioSystem and sets up the necessary component signatures and event subscriptions.
    */
    AudioSystem::AudioSystem() : ASystem()
    {
        _signature.set(AComponent::getID<AudioComponent>(), true);
        engine.subscribeEvent(this, &AudioSystem::updateSounds);
    }

    /*!
    * @brief Destroy the Audio System object.
    */
    AudioSystem::~AudioSystem() {

    }

    /*!
    * @brief Update the sounds.
    *
    * This function updates the sounds by checking the status of each audio component and playing or stopping the sound accordingly.
    *
    * @param event The event triggering the sound update.
    */
    void AudioSystem::updateSounds(std::shared_ptr<NoneEvent> event) {
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