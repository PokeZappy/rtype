/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-cyprien.diederichs
** File description:
** Component.hpp
*/

#ifndef ICOMPONENT_HPP
#define ICOMPONENT_HPP

namespace polEngine
{
    class IComponent {
    public:
        virtual ~IComponent() = default;
        virtual const char* getType() const = 0;
    };
}

#endif // ICOMPONENT_HPP
