#pragma once

#include "AComponent.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace potEngine
{
    /*!
    * @brief Component class for managing audio playback.
    */
    class AudioComponent : public AComponent {
    public:
        // AudioComponent() {};
        AudioComponent(std::string &fileName);
        AudioComponent(std::string &fileName, bool playOnLoop);
        ~AudioComponent();

        /*!
        * @brief Get the sound object.
        * @return Reference to the SFML Sound object.
        */
        sf::Sound &getSound() { return (_sound); }

        /*!
        * @brief Get the sound buffer object.
        * @return The SFML SoundBuffer object.
        */
        sf::SoundBuffer getSoundBuffer() { return (_buffer); }

        /*!
        * @brief Check if the audio is set to play on loop.
        * @return True if the audio is set to play on loop, false otherwise.
        */
        bool isOnLoop() { return (_playOnLoop); }

        /*!
        * @brief Check if the audio is currently playing.
        * @return True if the audio is playing, false otherwise.
        */
        bool isPlaying() { return (_isPlaying); }

        /*!
        * @brief Set the playing state of the audio.
        * @param state The new playing state.
        */
        void setPlaying(bool state) { _isPlaying = state; }
        private:
        sf::SoundBuffer _buffer;
        sf::Sound _sound;
        bool _playOnLoop;       // si le son doit se répéter
        bool _isPlaying = false;        // l'état de la lecture
    };
}
