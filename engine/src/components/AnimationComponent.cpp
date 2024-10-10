#include "AnimationComponent.hpp"

namespace potEngine {
    // Implementation
AnimationComponent::AnimationComponent(int maxFrames, float interval, bool looping, std::function<sf::IntRect(int)> changeFrame)
    : _maxFrames(maxFrames), _interval(interval), _looping(looping), _changeFrame(changeFrame) {
        _clock.restart();
    }

AnimationComponent::~AnimationComponent() {}

void AnimationComponent::setChangeFrame(std::function<sf::IntRect(int)> changeFrameFunc) {
    _changeFrame = changeFrameFunc;
}

std::function<sf::IntRect(int)> AnimationComponent::getChangeFrame() const {
    return _changeFrame;
}
};