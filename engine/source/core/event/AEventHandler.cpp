#include "AEventHandler.hpp"

namespace potEngine
{
    void AEventHandler::exec(std::shared_ptr<IEvent> evnt) 
    {
        call(evnt);
    }
}