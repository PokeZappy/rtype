#pragma once

#include "AComponent.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional>

namespace potEngine
{
    /*!
    * @brief Component class for managing animations.
    */
    class AnimationComponent : public AComponent {
    public:
        AnimationComponent(int maxFrames, float interval, bool looping, std::function<sf::IntRect(int)> changeFrame);
        ~AnimationComponent();

        /*!
        * \brief Set the function to change the frame.
        * \param changeFrameFunc The function to change the frame.
        */
        void setChangeFrame(std::function<sf::IntRect(int)> changeFrameFunc);

        /*!
        * \brief Get the function to change the frame.
        * \return The function to change the frame.
        */
        std::function<sf::IntRect(int)> getChangeFrame() const;

        /*!
        * \brief Get the maximum number of frames in the animation.
        * \return The maximum number of frames.
        */
        int getMaxFrames() { return (_maxFrames); }

        /*!
        * \brief Get the current frame of the animation.
        * \return The current frame.
        */
        int getActualFrame() { return (_actualFrame); }

        /*!
        * \brief Set the current frame of the animation.
        * \param frame The current frame.
        */
        void setActualFrame(int frame) { _actualFrame = frame; }

        /*!
        * \brief Get the time interval between frames.
        * \return The time interval.
        */
        float getInterval() { return (_interval); }

        /*!
        * \brief Check if the animation is set to loop.
        * \return True if the animation is looping, false otherwise.
        */
        bool isLooping() { return (_looping); }

        /*!
        * \brief Get the clock used for timing the animation.
        * \return Reference to the SFML Clock object.
        */
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

