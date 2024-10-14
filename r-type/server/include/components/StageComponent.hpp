#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "server_config.hpp"

typedef std::vector<int> Position;

namespace potEngine
{
    struct StageInfo
    {
        float _waves_time;
        std::vector<int> _apparition_time;
        std::vector<std::string> _monsters;
        std::vector<std::vector<Position>> _apparition_point;
        std::vector<int> _nb_monsters;
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
        int _actual_wave = 0;
        std::vector<std::shared_ptr<struct StageInfo>> _stageInfo;
    };
}