/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** main.cpp
*/

#include "../include/client_config.hpp"
#include "networking/socket.hpp"
#include "serializer/serializer.hpp"

int main()
{
    Socket clientSocket;
    std::string serverIp = "127.0.0.1";
    int serverPort = 12345;

    std::string senderIp;
    int senderPort;

    while (true) {
        std::string message;
        std::cout << "Enter message to send to server (type 'exit' to quit): ";
        std::getline(std::cin, message);
        BitSerializer serializer;

        if (message == "exit") {
            break;
        }
        if (message == "move") {
            serializer.writeBits(MOVE, 8);
            std::vector<uint8_t> buffer = serializer.getBuffer();
            std::string bufferStr(buffer.begin(), buffer.end());
            clientSocket.sendTo(serverIp, serverPort, bufferStr);
        } else if (message == "fire") {
            serializer.writeBits(FIRE, 8);
            std::vector<uint8_t> buffer = serializer.getBuffer();
            std::string bufferStr(buffer.begin(), buffer.end());
            clientSocket.sendTo(serverIp, serverPort, bufferStr);
        } else {
            clientSocket.sendTo(serverIp, serverPort, message);
        }
        std::string response = clientSocket.receiveFrom(senderIp, senderPort);
        serializer.clearBuffer();
        serializer.loadBuffer(std::vector<uint8_t>(message.begin(), message.end()));
        serializer.printBuffer();
        uint16_t messageType = serializer.readBits(8);
        if (messageType == MOVE) {
            std::cout << "Received move event\n";
        } else if (messageType == FIRE) {
            std::cout << "Received fire event\n";
        } else {
            std::cout << "Received unknown event\n";
        }
        std::cout << "Server response: " << response << std::endl;
    }
    return 0;
}