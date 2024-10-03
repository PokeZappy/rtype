#pragma once

#include <memory>

#include "IEvent.hpp"

namespace potEngine {
    class AEventHandler {
    public:
        virtual ~AEventHandler() = default;
        void exec(std::shared_ptr<IEvent> evnt);
    private:
        virtual void call(std::shared_ptr<IEvent> evnt) = 0;
    };
}
