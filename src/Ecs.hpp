/*
** EPITECH PROJECT, 2024
** synthese
** File description:
** Ecs.hpp
*/

#pragma once
#include "SparseArray.hpp"
#include <unordered_map>
#include <typeindex>
#include <any>

class ECS {
    public :
        ECS () ;
        ~ ECS () = default ;
        template <class Component>
        auto register_component() -> SparseArray<Component>&;

        template <class Component>
        auto get_components() -> SparseArray<Component>&;

        template <class Component>
        auto get_components() const -> const SparseArray<Component>&;
    private :
        std::unordered_map<std::type_index, std::any> _components_arrays;
};

#include "Ecs.inl"