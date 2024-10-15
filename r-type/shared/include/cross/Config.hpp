
#pragma once

#define BUFFER_SIZE 1024

#ifdef _WIN32
    // #define NOMINMAX
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #include <windows.h>
    #include <BaseTsd.h>
    #include <io.h>

    typedef SSIZE_T ssize_t;

    #define INIT_WINSOCK() \
    WSADATA wsaData; \
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    #define SET_NONBLOCKING(fd)\
    u_long mode = 1;\
    ioctlsocket(fd, FIONBIO, &mode);

    #define SET_SOCK_NONBLOCKING(fd)\
    u_long mode = 1; \
    ioctlsocket(client_fd, FIONBIO, &mode); \
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE); \
    DWORD modeStdin; \
    GetConsoleMode(hStdin, &modeStdin); \
    SetConsoleMode(hStdin, modeStdin & ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT));

    typedef int socklen_t;
    #define RECVFROM(clientFd, buffer, buffer_size, flags, addr, addr_len) \
    recvfrom(clientFd, (char *)buffer, buffer_size, flags, (struct sockaddr *)addr, (int *)addr_len)

    #define SENDTO(fd, packet, packet_size, flags, addr, addr_len) \
    sendto(fd, (const char *)packet, packet_size, flags, (const struct sockaddr *)addr, addr_len)

    #define CLOSESOCKET(clientFd) \
        closesocket(clientFd); \
        WSACleanup();

    #define READLINK(path, buffer, len) \
    GetModuleFileNameA(NULL, buffer, len);

#else
    #include <netinet/in.h>
    #include <termios.h>
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #include <stdint.h>
    #include <fcntl.h>
    #include <libconfig.h++>

    #define INIT_WINSOCK()

    #define SET_NONBLOCKING(fd) \
        int flags = fcntl(fd, F_GETFL, 0); \
        fcntl(fd, F_SETFL, flags | O_NONBLOCK);

    #define SET_SOCK_NONBLOCKING(fd)\
    struct termios t{}; \
    tcgetattr(STDIN_FILENO, &t); \
    t.c_lflag &= ~ICANON; \
    t.c_lflag &= ~ECHO; \
    tcsetattr(STDIN_FILENO, TCSANOW, &t); \
    int flags = fcntl(client_fd, F_GETFL, 0); \
    fcntl(client_fd, F_SETFL, flags | O_NONBLOCK); \
    int flags_ = fcntl(STDIN_FILENO, F_GETFL, 0); \
    fcntl(STDIN_FILENO, F_SETFL, flags_ | O_NONBLOCK);

    #define RECVFROM(clientFd, buffer, buffer_size, flags, addr, addr_len) \
    recvfrom(clientFd, buffer, buffer_size, flags, (struct sockaddr *)addr, (socklen_t *)addr_len)

    #define SENDTO(fd, packet, packet_size, flags, addr, addr_len) \
    sendto(fd, packet, packet_size, flags, (const struct sockaddr *)addr, addr_len)

    #define CLOSESOCKET(clientFd) \
    close(clientFd);

    #define READLINK(path, buffer, len) \
    readlink(path, buffer, len - 1);

#endif
