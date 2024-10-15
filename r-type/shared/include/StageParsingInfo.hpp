#pragma once

#include <vector>
#include <iostream>

typedef std::vector<int> Position;

namespace potEngine {
    struct StageInfo
    {
        float _waves_time;
        std::vector<int> _apparition_time;
        std::vector<std::string> _monsters;
        std::vector<std::vector<Position>> _apparition_point;
        std::vector<int> _nb_monsters;
    };

    struct EnemyInfo
    {
        std::string name;
        int id;
        int hp;
        int speed;
        int scoreValue;
        std::string movePattern;
        std::string attackPattern;
        std::string texturePath;
        std::vector<int> textureRect;
    };

    struct AttackPaternInfo
    {
        std::string type;
        size_t bulletSpeed;
        size_t bulletFrequency;
        std::string direction;
    };

    struct MovePatternInfo
    {
        std::string type;
        size_t speed;
        std::string direction;
    };
}