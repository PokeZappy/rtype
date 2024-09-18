#include <iostream>
#include <vector>
#include <cassert>
#include <bitset>
#include "serializer/serializer.h"

#define GREEN   "\033[32m"
#define RESET   "\033[0m"

void testWriteBits() {
    BitSerializer serializer;
    serializer.writeBits(0b101, 3);
    std::vector<uint8_t> buffer = serializer.getBuffer();
    assert(buffer.size() == 1);
    assert(buffer[0] == 0b10100000);
    std::cout << GREEN << "testWriteBits passed." << RESET << std::endl;
}

void testWriteBitsFromInt() {
    BitSerializer serializer;
    serializer.writeBits(2, 2);
    std::vector<uint8_t> buffer = serializer.getBuffer();
    assert(buffer.size() == 1);
    assert(buffer[0] == 0b10000000);
    std::cout << GREEN << "testWriteBitsFromInt passed." << RESET << std::endl;
}

void testWriteBitsFromBigInt() {
    BitSerializer serializer;
    serializer.writeBits(4895, 13);
    std::vector<uint8_t> buffer = serializer.getBuffer();
    assert(buffer.size() == 2);
    assert(buffer[0] == 0b10011000);
    assert(buffer[1] == 0b11111000);
    std::cout << GREEN << "testWriteBitsFromBigInt passed." << RESET << std::endl;
}


void testWriteBitsFromBigInt2() {
    BitSerializer serializer;
    serializer.writeBits(5681, 14);
    std::vector<uint8_t> buffer = serializer.getBuffer();
    assert(buffer.size() == 2);
    assert(buffer[0] == 0b01011000);
    assert(buffer[1] == 0b11000100);
    std::cout << GREEN << "testWriteBitsFromBigInt2 passed." << RESET << std::endl;
}

void testWriteBitsFromReallyBigInt() {
    BitSerializer serializer;
    serializer.writeBits(489566, 19);
    std::vector<uint8_t> buffer = serializer.getBuffer();
    assert(buffer.size() == 3);
    assert(buffer[0] == 0b11101111);
    assert(buffer[1] == 0b00001011);
    assert(buffer[2] == 0b11000000);
    std::cout << GREEN << "testWriteBitsFromReallyBigInt passed." << RESET << std::endl;
}

void testWriteBitsWithMoreNumBits() {
    BitSerializer serializer;
    serializer.writeBits(2, 8);
    std::vector<uint8_t> buffer = serializer.getBuffer();
    assert(buffer.size() == 1);
    assert(buffer[0] == 0b00000010);
    std::cout << GREEN << "testWriteBitsWithMoreNumBits passed." << RESET << std::endl;
}

void testReadBits() {
    BitSerializer serializer;
    serializer.writeBits(2, 2);
    std::vector<uint8_t> buffer = serializer.getBuffer();
    BitSerializer serializer2;
    serializer2.loadBuffer(buffer);
    uint32_t result = serializer2.readBits(2);
    assert(result == 2);
    std::cout << GREEN << "testReadBits passed." << RESET << std::endl;
}

void testReadBitsBigInt() {
    BitSerializer serializer;
    serializer.writeBits(4895, 13);
    std::vector<uint8_t> buffer = serializer.getBuffer();
    assert(buffer.size() == 2);
    assert(buffer[0] == 0b10011000);
    assert(buffer[1] == 0b11111000);
    BitSerializer serializer2;
    serializer2.loadBuffer(buffer);
    uint32_t result = serializer2.readBits(13);
    assert(result == 4895);
    std::cout << GREEN << "testReadBitsBigInt passed." << RESET << std::endl;
}

void testReadBitsFromReallyBigInt() {
    BitSerializer serializer;
    serializer.writeBits(489566, 19);
    std::vector<uint8_t> buffer = serializer.getBuffer();
    BitSerializer serializer2;
    serializer2.loadBuffer(buffer);
    uint32_t result = serializer2.readBits(19);
    assert(result == 489566);
    std::cout << GREEN << "testWriteBitsFromReallyBigInt passed." << RESET << std::endl;
}

void testReadBitsWithMoreNumBits() {
    BitSerializer serializer;
    serializer.writeBits(2, 8);
    std::vector<uint8_t> buffer = serializer.getBuffer();
    BitSerializer serializer2;
    serializer2.loadBuffer(buffer);
    uint32_t result = serializer2.readBits(8);
    assert(result == 2);
    std::cout << GREEN << "testReadBitsWithMoreNumBits passed." << RESET << std::endl;
}

void testComplexOne() {
    BitSerializer serializer;

    uint32_t playerId = 1234;
    int16_t posX = 300;
    int16_t posY = 500;
    int8_t velocityX = 90;
    int8_t velocityY = -45;

    serializer.writeBits(MOVE, 8);
    serializer.writeBits(playerId, 12);
    serializer.writeBits(posX, 12);
    serializer.writeBits(posY, 12);
    serializer.writeBits(velocityX, 8);
    serializer.writeBits(velocityY, 8);
    std::vector<uint8_t> buffer = serializer.getBuffer();
    serializer.loadBuffer(buffer);
    serializer.readBits(8);
    MovementMessage movementMessage = serializer.deserialize<MovementMessage>(buffer);
    assert(movementMessage.playerId == 1234);
    assert(movementMessage.posX == 300);
    assert(movementMessage.posY == 500);
    assert(movementMessage.velocityX == 90);
    assert(movementMessage.velocityY == -45);
    std::cout << GREEN << "testComplexOne passed." << RESET << std::endl;
}

void testComplexTwo() {
    BitSerializer fireSerializer;
    uint32_t firePlayerId = 4000;
    int16_t firePosX = 250;
    int16_t firePosY = 400;
    uint8_t direction = 2;

    fireSerializer.writeBits(FIRE, 8);
    fireSerializer.writeBits(firePlayerId, 12);
    fireSerializer.writeBits(firePosX, 12);
    fireSerializer.writeBits(firePosY, 12);
    fireSerializer.writeBits(direction, 8);
    std::vector<uint8_t> fireBuffer = fireSerializer.getBuffer();
    fireSerializer.loadBuffer(fireBuffer);
    fireSerializer.readBits(8);
    FireMessage fireMessage = fireSerializer.deserialize<FireMessage>(fireBuffer);
    assert(fireMessage.playerId == 4000);
    assert(fireMessage.posX == 250);
    assert(fireMessage.posY == 400);
    assert(fireMessage.direction == 2);
    std::cout << GREEN << "testComplexTwo passed." << RESET << std::endl;
}

int main() {
    // WriteBits
    testWriteBits();
    testWriteBitsFromInt();
    testWriteBitsFromBigInt();
    testWriteBitsFromBigInt2();
    testWriteBitsFromReallyBigInt();
    testWriteBitsWithMoreNumBits();
    // ReadBits
    testReadBits();
    testReadBitsBigInt();
    testReadBitsWithMoreNumBits();
    testReadBitsFromReallyBigInt();
    // Complex tests
    testComplexOne();
    testComplexTwo();
    std::cout << "All tests completed." << std::endl;
    return 0;
}