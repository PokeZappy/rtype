#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "AComponent.hpp"

typedef std::vector<int> Position;

namespace potEngine
{
    struct StageInfo
    {
        float _waves_time;
        std::vector<float> _apparition_time;
        std::vector<std::string> _monsters;
        std::vector<Position> _apparition_point;
    };

    class StageComponent : public AComponent
    {
    public:
        StageComponent() = default;
        ~StageComponent() = default;
        int _level = 0;
        bool _isStarted = false;
        sf::Clock _clock = sf::Clock();
        float _start_time = 0;
        std::vector<struct StageInfo> _stageInfo;
    };
}