#include <iostream>
#include <string>
#include <cassert>

std::string helloWorld() {
    return "Hello, World!";
}

int main() {
    assert(helloWorld() == "Hello, World!");
    std::cout << "Test passed: helloWorld() returns 'Hello, World!'" << std::endl;
    return 0;
}