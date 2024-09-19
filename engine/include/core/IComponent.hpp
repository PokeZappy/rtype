#pragma once

#include <cstdint>
#include <atomic>
#include <typeinfo>

namespace potEngine {
    class IComponent {
    public:
        virtual ~IComponent() = default;

        virtual std::uint32_t getID() const = 0;
    };
}