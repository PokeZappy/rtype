#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "AComponent.hpp"

namespace potEngine
{
    class AudioComponent : public AComponent {
    public:
        // AudioComponent() {};
        AudioComponent(std::string &fileName);
        AudioComponent(std::string &fileName, bool playOnLoop);
        ~AudioComponent();

        sf::Sound &getSound() { return (_sound); }
        sf::SoundBuffer getSoundBuffer() { return (_buffer); }
        bool isOnLoop() { return (_playOnLoop); }
        bool isPlaying() { return (_isPlaying); }
        void setPlaying(bool state) { _isPlaying = state; }
        private:
        sf::SoundBuffer _buffer;
        sf::Sound _sound;
        bool _playOnLoop;       // si le son doit se répéter
        bool _isPlaying = false;        // l'état de la lecture
    };
}
