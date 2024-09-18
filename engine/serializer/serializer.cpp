/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-cyprien.diederichs
** File description:
** serializer.cpp
*/

#include "serializer.h"

void BitSerializer::writeBits(uint32_t data, uint8_t numBits) {
    for (int i = numBits - 1; i >= 0; --i) {
        currentByte |= ((data >> i) & 1) << (7 - bitIndex);
        bitIndex++;

        if (bitIndex == 8) {
            buffer.push_back(currentByte);
            bitIndex = 0;
            currentByte = 0;
        }
    }
}

uint32_t BitSerializer::readBits(uint8_t numBits) {
    uint32_t result = 0;

    for (int i = numBits - 1; i >= 0; --i) {
        if (bitIndex == 8) {
            bitIndex = 0;
            if (bufferIndex >= buffer.size()) {
                throw std::out_of_range("Index is out of range");
            }
            bufferIndex++;
            currentByte = buffer[bufferIndex];
        }

        result |= ((currentByte >> (7 - bitIndex)) & 1) << i;
        bitIndex++;
    }
    return result;
}

std::vector<uint8_t> BitSerializer::getBuffer() const {
    std::vector<uint8_t> finalBuffer = buffer;
    if (bitIndex > 0) {
        finalBuffer.push_back(currentByte);
    }
    return finalBuffer;
}

void BitSerializer::loadBuffer(const std::vector<uint8_t>& newBuffer) {
    buffer = newBuffer;
    bufferIndex = 0;
    bitIndex = 0;
    currentByte = buffer.empty() ? 0 : buffer[0];
}

void BitSerializer::printBuffer() const {
    for (auto byte : buffer) {
        for (int i = 7; i >= 0; --i) {
            std::cout << ((byte >> i) & 1);
        }
        std::cout << " ";
    }
    std::cout << std::endl;
}

template <>
MovementMessage BitSerializer::deserialize<MovementMessage>(const std::vector<uint8_t>& buffer) {
    size_t index = 0;
    MovementMessage msg;

    msg.playerId = readBits(12);
    msg.posX = readBits(12);
    msg.posY = readBits(12);
    msg.velocityX = readBits(8);
    msg.velocityY = readBits(8);

    return msg;
}

template <>
FireMessage BitSerializer::deserialize<FireMessage>(const std::vector<uint8_t>& buffer) {
    size_t index = 0;
    FireMessage msg;

    msg.playerId = readBits(12);
    msg.posX = readBits(12);
    msg.posY = readBits(12);
    msg.direction = readBits(8);

    return msg;
}