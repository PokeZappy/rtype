#pragma once

#include <iostream>
#include <filesystem>
#include <stdexcept>
#include <unistd.h>

namespace Rtype {
    class Core {
    public:
         Core(const std::string &assetsPath) : _assetsRoot(assetsPath) {};
        ~Core() = default;

    private:
        std::string _assetsRoot;
    };
}
