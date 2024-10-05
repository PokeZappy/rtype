
#pragma once


#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #include <windows.h>

#else
    #include <netinet/in.h>
    #include <termios.h>

#endif
