/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** socket.cpp
*/

#include "socket.hpp"

Socket::Socket() : sockfd(-1) {
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }
}

Socket::~Socket() {
    if (sockfd >= 0) {
        close(sockfd);
    }
}

void Socket::bindSocket(const std::string& ipAddress, int port) {
    struct sockaddr_in localAddr;
    memset(&localAddr, 0, sizeof(localAddr));
    localAddr.sin_family = AF_INET;
    localAddr.sin_port = htons(port);

    if (inet_pton(AF_INET, ipAddress.c_str(), &localAddr.sin_addr) <= 0) {
        perror("Invalid IP address");
        exit(EXIT_FAILURE);
    }

    if (bind(sockfd, (struct sockaddr*)&localAddr, sizeof(localAddr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }
}

void Socket::sendTo(const std::string& ipAddress, int port, const std::string& data) {
    struct sockaddr_in destAddr;
    memset(&destAddr, 0, sizeof(destAddr));
    destAddr.sin_family = AF_INET;
    destAddr.sin_port = htons(port);

    if (inet_pton(AF_INET, ipAddress.c_str(), &destAddr.sin_addr) <= 0) {
        perror("Invalid IP address");
        exit(EXIT_FAILURE);
    }

    ssize_t sentBytes = sendto(sockfd, data.c_str(), data.size(), 0,
                               (struct sockaddr*)&destAddr, sizeof(destAddr));
    if (sentBytes < 0) {
        perror("Send failed");
    }
}

std::string Socket::receiveFrom(std::string& senderIp, int& senderPort) {
    char buffer[1024];
    struct sockaddr_in senderAddr;
    socklen_t senderAddrLen = sizeof(senderAddr);

    ssize_t receivedBytes = recvfrom(sockfd, buffer, sizeof(buffer) - 1, 0,
                                     (struct sockaddr*)&senderAddr, &senderAddrLen);
    if (receivedBytes < 0) {
        perror("Receive failed");
        return "";
    }

    buffer[receivedBytes] = '\0';

    char senderIpBuffer[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &senderAddr.sin_addr, senderIpBuffer, INET_ADDRSTRLEN);
    senderIp = std::string(senderIpBuffer);
    senderPort = ntohs(senderAddr.sin_port);

    return std::string(buffer);
}
