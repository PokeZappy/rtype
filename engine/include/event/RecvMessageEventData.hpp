#pragma once

#include <memory>
#include <vector>

#include "IEvent.hpp"
#include <netinet/in.h>
// #include "MainLoopEvent.hpp"

namespace potEngine {
    class MainLoopEvent;
    struct RecvMessageEventData : public IEvent {
        RecvMessageEventData(int cliFd, struct sockaddr_in servAddr, socklen_t adLen, uint8_t id) : serverAddr(servAddr), addrLen(adLen), playerId(id), clientFd(cliFd) {}
        struct sockaddr_in serverAddr;
        socklen_t addrLen;
        uint8_t playerId;
        int clientFd;
    };
}
