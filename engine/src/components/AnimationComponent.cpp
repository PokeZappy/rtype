#include "AnimationComponent.hpp"

namespace potEngine {
    // Implementation
/*!
* @brief Construct a new AnimationComponent object.
*
* This constructor initializes the AnimationComponent with the given parameters.
*
* @param maxFrames The maximum number of frames in the animation.
* @param interval The time interval between frames.
* @param looping Whether the animation should loop.
* @param changeFrame A function to change the frame.
*/
AnimationComponent::AnimationComponent(int maxFrames, float interval, bool looping, std::function<sf::IntRect(int)> changeFrame)
    : _maxFrames(maxFrames), _interval(interval), _looping(looping), _changeFrame(changeFrame) {
        _clock.restart();
    }

/*!
* @brief Destroy the AnimationComponent object.
*/
AnimationComponent::~AnimationComponent() {}

/*!
* @brief Set the function to change the frame.
*
* @param changeFrameFunc The function to change the frame.
*/
void AnimationComponent::setChangeFrame(std::function<sf::IntRect(int)> changeFrameFunc) {
    _changeFrame = changeFrameFunc;
}

/*!
* @brief Get the function to change the frame.
*
* @return The function to change the frame.
*/
std::function<sf::IntRect(int)> AnimationComponent::getChangeFrame() const {
    return _changeFrame;
}
};