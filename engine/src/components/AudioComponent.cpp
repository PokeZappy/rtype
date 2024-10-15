#include "AudioComponent.hpp"

namespace potEngine {

    /*!
    * @brief Construct a new AudioComponent object with the given file name.
    *
    * This constructor initializes the AudioComponent with the given file name and sets the sound buffer.
    *
    * @param fileName The name of the audio file.
    */
    AudioComponent::AudioComponent(std::string &fileName) {
        _buffer.loadFromFile(fileName);
        _sound.setBuffer(_buffer);
        _playOnLoop = false;
        _sound.setLoop(_playOnLoop);
    }

    /*!
    * @brief Construct a new AudioComponent object with the given file name and loop setting.
    *
    * This constructor initializes the AudioComponent with the given file name and sets the sound buffer and loop setting.
    *
    * @param fileName The name of the audio file.
    * @param playOnLoop Whether the sound should play on loop.
    */
    AudioComponent::AudioComponent(std::string &fileName, bool playOnLoop) {
        _buffer.loadFromFile(fileName);
        _sound.setBuffer(_buffer);
        _playOnLoop = playOnLoop;
        _sound.setLoop(_playOnLoop);
    }

    /*!
    * @brief Destroy the AudioComponent object.
    */
    AudioComponent::~AudioComponent() {}
};