#pragma once

#include <cstdint>
#include <atomic>
#include <typeinfo>

namespace potEngine {
    class IComponent {
    public:
        virtual ~IComponent() = default;
    };
}