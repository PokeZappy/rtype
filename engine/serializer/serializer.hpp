/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-cyprien.diederichs
** File description:
** serializer.hpp
*/

#ifndef RTYPE_SERIALIZER_HPP
#define RTYPE_SERIALIZER_HPP

#include <vector>
#include <cstdint>
#include <cstring>
#include <stdexcept>
#include <iostream>

enum MessageType {
    MOVE = 0x01,
    FIRE = 0x02,
};

struct MovementMessage {
    uint32_t playerId;
    int16_t posX;
    int16_t posY;
    int8_t velocityX;
    int8_t velocityY;
};

struct FireMessage {
    uint32_t playerId;
    int16_t posX;
    int16_t posY;
    uint8_t direction;
};

class BitSerializer {
public:
    BitSerializer() : bitIndex(0), currentByte(0) {}

    void writeBits(uint32_t data, uint8_t numBits);
    uint32_t readBits(uint8_t numBits);
    std::vector<uint8_t> getBuffer() const;
    void loadBuffer(const std::vector<uint8_t>& newBuffer);
    void printBuffer() const;
    void clearBuffer();

    template <typename T>
    T deserialize();

private:
    std::vector<uint8_t> buffer;
    uint8_t bitIndex = 0;
    uint8_t currentByte = 0;
    size_t bufferIndex = 0;
};

template <>
MovementMessage BitSerializer::deserialize<MovementMessage>();

template <>
FireMessage BitSerializer::deserialize<FireMessage>();


#endif
