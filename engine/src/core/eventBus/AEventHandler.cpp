#include "AEventHandler.hpp"

namespace potEngine
{
    /*!
    * @brief Execute the event handler.
    *
    * This function calls the event handler with the given event.
    *
    * @param evnt The event to handle.
    */
    void AEventHandler::exec(std::shared_ptr<IEvent> evnt) 
    {
        call(evnt);
    }
}