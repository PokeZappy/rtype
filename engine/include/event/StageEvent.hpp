#pragma once

#include <SFML/System.hpp>
#include <iostream>

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
        };

        void StageGame(std::shared_ptr<StageInfoEvent> info)
        {
            auto stageComponent = info->_stage->getComponent<StageComponent>();
            if (stageComponent == std::nullopt) {
                return;
            }
            auto stage = stageComponent->get();
            if (stage->_actual_wave == 0 && stage->_clock.getElapsedTime().asSeconds() < stage->_start_time) {
                eventBus.publish(info);
                return;
            }
            if (stage->_actual_wave == 0) {
                stage->_clock.restart();
                stage->_actual_wave = 1;
            }
            if ((std::size_t) stage->_actual_wave > stage->_stageInfo.size()) {
                eventBus.publish(info);
                return;
            }
            struct StageInfo wave = stage->_stageInfo[stage->_actual_wave - 1];
            std::shared_ptr<AEntity> monster;
            for (std::size_t i = 0; i < wave._monsters.size(); i++) {
                if (stage->_clock.getElapsedTime().asSeconds() > wave._apparition_time[i] * wave._nb_monsters[i] / wave._waves_time) {
                    monster = ecsManager.createEntity();
                    std::shared_ptr<PositionComponent> comp;
                    std::cout << "monster: " << wave._monsters[i] << std::endl;
                    for (int j = 0; j < wave._apparition_point.size(); j++) {
                        for (int k = 0; k < wave._apparition_point[j].size(); k++) {
                            std::cout << "apparition_point: " << wave._apparition_point[j][k][0] << " " << wave._apparition_point[j][k][1] << std::endl;
                        }
                    }
                    // if (wave._apparition_point[i] == std::vector<int>{-1, -1}) {
                    //     comp = std::make_shared<PositionComponent>(-1, -1);
                    //     ecsManager.addComponent(monster, comp);
                    // } else {
                    //     comp = std::make_shared<PositionComponent>(wave._apparition_point[i][0], wave._apparition_point[i][1]);
                    //     ecsManager.addComponent(monster, comp);
                    // }
                    // ecsManager.addComponent(monster, comp);
                    // wave._nb_monsters[i]++;
                }
            }
            if (stage->_clock.getElapsedTime().asSeconds() > wave._waves_time) {
                stage->_actual_wave++;
                stage->_clock.restart();
            }
            eventBus.publish(info);
        }
    };
}
