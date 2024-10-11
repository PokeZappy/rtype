#pragma once

#include <libconfig.h++>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <memory>

#include "IEvent.hpp"
#include "EventBus.hpp"
#include "ECSManager.hpp"
#include "StageComponent.hpp"
#include "game_config.hpp"
#include "AssetFinder.hpp"
#include "StageEvent.hpp"

namespace potEngine
{
    class StratStageInfoEvent : public IEvent
    {
    public:
        int max_players;
        int fd;
        EventType event = EventType::START_STAGE;
        uint8_t entity_id;
        std::vector<unsigned short> _params;

            StratStageInfoEvent(const int maxPlayers, int serverFd, unsigned char entityId, std::vector<unsigned short>& params)
            : max_players(maxPlayers), fd(serverFd), entity_id(entityId), _params(params) {}
    };

    class StartStageEvent : public IEvent
    {
    public:
        StartStageEvent() {
            eventBus.subscribe(this, &StartStageEvent::StartStage);
        };

        void StartStage(std::shared_ptr<StratStageInfoEvent> info)
        {
            std::optional<std::shared_ptr<potEngine::StageComponent>> stageComponent = std::nullopt;
            std::shared_ptr<potEngine::AEntity> entity;

            for (auto entity : ecsManager.getEntities()) {
                if (entity->hasComponent<StageComponent>()) {
                    stageComponent = entity->getComponent<StageComponent>();
                    return;
                }
            }
            if (stageComponent == std::nullopt) {
                entity = ecsManager.createEntity();
                auto newStageComponent = std::make_shared<StageComponent>();
                ecsManager.addComponent(entity, newStageComponent);
                stageComponent = newStageComponent;
            }
            stageComponent->get()->_level++;
            try {
                libconfig::Config cfg;
                cfg.readFile(potEngine::assetFinder() + "/../server/config/stage_" + std::to_string(stageComponent->get()->_level) + ".cfg");
                libconfig::Setting &root = cfg.getRoot();
                stageComponent->get()->_clock.restart();
                stageComponent->get()->_start_time = root["stage_info"]["start_time"];
                stageComponent->get()->_stageInfo.clear();
                for (int i = 0; i < root["waves"].getLength(); i++) {
                    struct StageInfo stageInfo;
                    libconfig::Setting &waves = root["waves"]["wave_" + std::to_string(i + 1)];
                    stageInfo._waves_time = waves["wave_time"];
                    for (int j = 0; j < waves["apparition_time"].getLength(); j++) {
                        stageInfo._monsters.push_back(waves["monsters"][j]);
                        stageInfo._apparition_time.push_back(waves["apparition_time"][j]);
                        stageInfo._nb_monsters.push_back(0);
                        const libconfig::Setting &valueArray = waves["apparition_point"][j];
                        for (int k = 0; k < valueArray.getLength(); k++) {
                            std::vector<std::vector<int>> all_pos;
                            for (int l = 0; l < valueArray[k]["value"].getLength(); l++) {
                                std::cout << "valueArray[k]: " << k << std::endl;
                                std::vector<int> pos = {-1, -1};
                                if (valueArray[k]["value"][l].getLength() != 0) {
                                    pos[0] = valueArray[k]["x"];
                                    pos[1] = valueArray[k]["y"];
                                }
                                all_pos.push_back(pos);
                            }
                            stageInfo._apparition_point.push_back(all_pos);
                        }
                    stageComponent->get()->_stageInfo.push_back(stageInfo);
                    stageComponent->get()->_isStarted = true;
                    }
                }
            } catch (const libconfig::FileIOException &fioex) {
                std::cerr << "I/O error while reading file." << std::endl;
                return;
            } catch (const libconfig::ParseException &pex) {
                std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine() << " - " << pex.getError() << std::endl;
                return;
            } catch (const libconfig::SettingNotFoundException &nfex) {
                std::cerr << "Setting not found in configuration file." << nfex.getPath() << std::endl;
                return;
            } catch (const libconfig::SettingTypeException &stex) {
                std::cerr << "Setting type error in configuration file." << stex.getPath() << std::endl;
                return;
            }
            eventBus.publish(std::make_shared<StageInfoEvent>(entity));
        };
    };
}