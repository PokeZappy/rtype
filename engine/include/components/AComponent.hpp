/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-cyprien.diederichs
** File description:
** Component.hpp
*/

#ifndef ACOMPONENT_HPP
#define ACOMPONENT_HPP

#include "IComponent.hpp"
#include <string>

namespace polEngine
{
    class AComponent : public IComponent {
    protected:
        std::string _type;

    public:
        AComponent(const std::string& type) : _type(type) {}
        virtual ~AComponent() {}

        const char* getType() const override
        {
            return _type.c_str();
        }
    };
}

#endif // ACOMPONENT_HPP
