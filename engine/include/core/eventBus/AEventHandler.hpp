#pragma once

#include <memory>

#include "IEvent.hpp"

namespace potEngine {
    /*!
    * @brief Get the next handler for an event.
    * @return A pair containing the event and the handler list.
    */
    class AEventHandler {
    public:
        /*!
        * @brief Virtual destructor for AEventHandler.
        */
        virtual ~AEventHandler() = default;
        void exec(std::shared_ptr<IEvent> evnt);
    private:
        /*!
        * @brief Virtual destructor for AEventHandler.
        */
        virtual void call(std::shared_ptr<IEvent> evnt) = 0;
    };
}
