#include "AudioComponent.hpp"

namespace potEngine {
    AudioComponent::AudioComponent(const std::string &fileName, bool playOnLoop, bool isPlaying) {
        _buffer.loadFromFile(fileName);
        _sound.setBuffer(_buffer);
        _playOnLoop = playOnLoop;
        _isPlaying = isPlaying;
        _sound.setLoop(_playOnLoop);
    }
    
    AudioComponent::~AudioComponent() = default;
};