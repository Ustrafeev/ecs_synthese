/*
** EPITECH PROJECT, 2024
** synthese
** File description:
** Ecs.inl
*/

#pragma once
#include "Ecs.hpp"

ECS::ECS() = default;

template <class Component>
auto ECS::register_component() -> SparseArray<Component>&
{
    std::type_index index(typeid(Component));
    if (_components_arrays.find(index) == _components_arrays.end())
        _components_arrays.emplace(index, std::make_any<SparseArray<Component>>());
    return std::any_cast<SparseArray<Component>&>(_components_arrays[index]);
}

template <class Component>
auto ECS::get_components() -> SparseArray<Component>&
{
    std::type_index index(typeid(Component));
    // if (_components_arrays.find(index) != _components_arrays.end())
    return std::any_cast<SparseArray<Component>&>(_components_arrays[index]);
}

template <class Component>
auto ECS::get_components() const -> const SparseArray<Component>&
{
    std::type_index index(typeid(Component));
    // if (_components_arrays.find(index) != _components_arrays.end())
    return std::any_cast<const SparseArray<Component>&>(_components_arrays.at(index));
}
