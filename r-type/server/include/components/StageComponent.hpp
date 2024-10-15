#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "server_config.hpp"

typedef std::vector<int> Position;

namespace potEngine
{

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
        std::vector<std::shared_ptr<struct EnemyInfo>> _enemies;
    };
}