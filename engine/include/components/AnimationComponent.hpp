#pragma once

#include <iostream>
#include <functional>

#include <SFML/Graphics.hpp>

#include "AComponent.hpp"

namespace potEngine
{
    class AnimationComponent : public AComponent {
    public:
        AnimationComponent(int maxFrames, float interval, bool looping, std::function<sf::IntRect(int, int)> changeFrame, int offset = 0);
        ~AnimationComponent();

        void setChangeFrame(std::function<sf::IntRect(int, int)> changeFrameFunc);
        std::function<sf::IntRect(int, int)> getChangeFrame() const;
        int getMaxFrames() { return (_maxFrames); }
        int getActualFrame() { return (_actualFrame); }
        void setActualFrame(int frame) { _actualFrame = frame; }
        float getInterval() { return (_interval); }
        bool isLooping() { return (_looping); }
        sf::Clock &getClock() { return (_clock); }
        int getAnimationOffset() { return (_offset); }
        void mustDestroyOnEnding(bool state) { _mustDestroyOnEnding = state; }
        bool getMustDestroyOnEnding() { return (_mustDestroyOnEnding); }
    private:
        int _maxFrames;
        int _actualFrame = 0;
        sf::Clock _clock;
        float _interval;
        bool _looping;
        std::function<sf::IntRect(int, int)> _changeFrame;
        int _offset = 0;
        bool _mustDestroyOnEnding = false;
    };
}

