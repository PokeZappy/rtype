#pragma once

#include <SFML/System.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "IEvent.hpp"
#include "EventBus.hpp"
#include "StageComponent.hpp"
#include "ECSManager.hpp"

namespace potEngine
{
    class StageInfoEvent : public IEvent
    {
    public:
        StageInfoEvent() {};
        StageInfoEvent(std::shared_ptr<AEntity> stage) : _stage(stage) {};
        ~StageInfoEvent() {};
        std::shared_ptr<AEntity> _stage; 

    };

    class StageEvent : public IEvent
    {
    public:
        StageEvent() {
            eventBus.subscribe(this, &StageEvent::StageGame);
            std::srand(time(nullptr));
        };

        void StageGame(std::shared_ptr<StageInfoEvent> info)
        {
            auto stageComponent = info->_stage->getComponent<StageComponent>();
            if (stageComponent == std::nullopt) {
                return;
            }
            auto stage = stageComponent->get();
            if ((std::size_t) stage->_actual_wave > stage->_stageInfo.size())
                return;
            if (stage->_actual_wave == 0 && stage->_clock.getElapsedTime().asSeconds() < stage->_start_time) {
                eventBus.publish(info);
                return;
            }
            if (stage->_actual_wave == 0) {
                stage->_clock.restart();
                stage->_actual_wave = 1;
            }
            std::shared_ptr<struct StageInfo> wave = stage->_stageInfo[stage->_actual_wave - 1];
            if (wave->_waves_time < stage->_clock.getElapsedTime().asSeconds()) {
                stage->_actual_wave++;
                stage->_clock.restart();
            }
            std::shared_ptr<AEntity> monster;
            for (std::size_t i = 0; i < wave->_monsters.size(); i++) {
                if (stage->_clock.getElapsedTime().asSeconds() >  wave->_nb_monsters[i] * wave->_waves_time / (wave->_apparition_time[i])) {
                    if (i == 0) {
                        std::cout << std::endl << "actual_wave: " << stage->_actual_wave << " stage size: " << (int) stage->_stageInfo.size() << std::endl; 
                        std::cout << "timer: " << stage->_clock.getElapsedTime().asSeconds() << std::endl << std::endl;
                        std::cout << "actual_time: " << stage->_clock.getElapsedTime().asSeconds() << std::endl;
                        std::cout << "waves_time: " << wave->_waves_time << std::endl;

                    }
                    std::cout << "apparition_time: " << wave->_apparition_time[i] << std::endl;
                    monster = ecsManager.createEntity();
                    std::shared_ptr<PositionComponent> comp;
                    std::cout << "monster: " << wave->_monsters[i] << std::endl;
                    // for (std::size_t j = 0; j < wave->_apparition_point->size(); j++) {
                    //     for (std::size_t k = 0; k < wave->_apparition_point[j]->size(); k++) {
                    //         std::cout << "apparition_point: " << wave->_apparition_point[j][k][0] << " " << wave->_apparition_point[j][k][1] << std::endl;
                    //     }
                    // }
                    if (wave->_apparition_point[i][0] == std::vector<int>{-1, -1}) {
                        // comp = std::make_shared<PositionComponent>(-1, -1);
                        // ecsManager->addComponent(monster, comp);
                        int rand_pos_left_srceen = rand() % 1080;
                        std::cout << "apparition_point: 1920, " << rand_pos_left_srceen << std::endl;
                    } else {
                        int rand_pos = std::rand() % wave->_apparition_point[i].size();
                        std::cout << "apparition_point: " << wave->_apparition_point[i][rand_pos][0] << ", " << wave->_apparition_point[i][rand_pos][1] << std::endl;
                        // comp = std::make_shared<PositionComponent>(wave->_apparition_point[i][0], wave->_apparition_point[i][1]);
                        // ecsManager->addComponent(monster, comp);
                    }
                    ecsManager.addComponent(monster, comp);
                    wave->_nb_monsters[i]++;
                    std::cout << "nb_monsters: " << wave->_nb_monsters[i] << std::endl << std::endl;
                }
            }
            eventBus.publish(info);
        }
    };
}
