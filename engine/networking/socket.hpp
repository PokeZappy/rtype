/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** server_socket.hpp
*/

#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <iostream>
#include <cstring>
#include <unistd.h>     // For close()
#include <arpa/inet.h>  // For inet_pton() and inet_ntop()
#include <sys/socket.h> // For socket(), bind(), sendto(), recvfrom()
#include <netinet/in.h> // For sockaddr_in

class Socket {
public:
    Socket();
    ~Socket();

    void bindSocket(const std::string& ipAddress, int port);
    void sendTo(const std::string& ipAddress, int port, const std::string& data);
    std::string receiveFrom(std::string& senderIp, int& senderPort);

private:
    int sockfd;
};

#endif // SOCKET_HPP
