/*
** EPITECH PROJECT, 2024
** synthese
** File description:
** ecs.hpp
*/

#pragma once
#include <cstddef>

class Entity {
    private:
        std::size_t size;
    public:
        explicit Entity(std::size_t nb = 0);
        ~Entity() = default;
        operator std::size_t() const;
};