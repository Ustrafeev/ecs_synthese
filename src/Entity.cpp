/*
** EPITECH PROJECT, 2024
** synthese
** File description:
** Ecs.cpp
*/

#include "Entity.hpp"

Entity::Entity(std::size_t nb) : size(nb) {}

Entity::operator std::size_t() const {
    return this->size;
}

