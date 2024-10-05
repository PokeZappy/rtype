#pragma once

#include "AComponent.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional>

namespace potEngine
{
    class AnimationComponent : public AComponent {
    public:
        AnimationComponent(int maxFrames, float interval, bool looping, std::function<sf::IntRect(int)> changeFrame);
        ~AnimationComponent();

        void setChangeFrame(std::function<sf::IntRect(int)> changeFrameFunc);
        std::function<sf::IntRect(int)> getChangeFrame() const;
        int getMaxFrames() { return (_maxFrames); }
        int getActualFrame() { return (_actualFrame); }
        void setActualFrame(int frame) { _actualFrame = frame; }
        float getInterval() { return (_interval); }
        bool isLooping() { return (_looping); }
        sf::Clock &getClock() { return (_clock); }
    private:
        int _maxFrames;
        int _actualFrame = 0;
        sf::Clock _clock;
        float _interval;
        bool _looping;
        std::function<sf::IntRect(int)> _changeFrame;
    };
}

