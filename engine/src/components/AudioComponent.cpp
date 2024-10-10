#include "AudioComponent.hpp"

namespace potEngine {
    AudioComponent::AudioComponent(std::string &fileName) {
        _buffer.loadFromFile(fileName);
        _sound.setBuffer(_buffer);
        _playOnLoop = false;
        _sound.setLoop(_playOnLoop);
    }

    AudioComponent::AudioComponent(std::string &fileName, bool playOnLoop) {
        _buffer.loadFromFile(fileName);
        _sound.setBuffer(_buffer);
        _playOnLoop = playOnLoop;
        _sound.setLoop(_playOnLoop);
    }
    
    AudioComponent::~AudioComponent() {}
};