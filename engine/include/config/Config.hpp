#pragma once

#include <libconfig.h++>
#include <string>

namespace potEngine {
    class Config {
    public:
        static Config& getInstance() {
            static Config instance;
            return instance;
        }
        Config(Config const&) = delete;
        void operator=(Config const&) = delete;

        void loadConfig(const std::string& path);
        libconfig::Setting& getSetting(const std::string& path);
        void saveConfig(const std::string& path);

    private:
        Config() = default;
        libconfig::Config _config;
    };
    static Config& config = Config::getInstance();
}