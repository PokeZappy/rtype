#include "Config.hpp"

void potEngine::Config::loadConfig(const std::string& path) {
    _config.readFile(path.c_str());
}

libconfig::Setting& potEngine::Config::getSetting(const std::string& path) {
    return _config.lookup(path);
}

void potEngine::Config::saveConfig(const std::string& path) {
    _config.writeFile(path.c_str());
}