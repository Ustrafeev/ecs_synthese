/*
** EPITECH PROJECT, 2024
** synthese
** File description:
** Ecs.inl
*/

#pragma once
#include "Ecs.hpp"

ECS::ECS() : _nb_entities(0) {}

template <class Component>
auto ECS::register_component() -> SparseArray<Component>&
{
    std::type_index index(typeid(Component));
    if (_components_arrays.find(index) == _components_arrays.end()) {
        _components_arrays.emplace(index, std::make_any<SparseArray<Component>>());
        auto lambda = [this](const Entity &entity) {
            remove_component<Component>(entity);
        };
        _freset_entity_components.push_back(lambda);
    }
    return std::any_cast<SparseArray<Component>&>(_components_arrays[index]);
}

template <class Component>
auto ECS::get_components() -> SparseArray<Component>&
{
    auto index = std::type_index(typeid(Component));
    //std::type_index index(typeid(Component));
    // if (_components_arrays.find(index) != _components_arrays.end())
    return std::any_cast<SparseArray<Component>&>(_components_arrays.at(index));
}

template <class Component>
auto ECS::get_components() const -> const SparseArray<Component>&
{
    std::type_index index(typeid(Component));
    // if (_components_arrays.find(index) != _components_arrays.end())
    return std::any_cast<const SparseArray<Component>&>(_components_arrays.at(index));
}

inline auto ECS::spawn_entity() -> Entity
{
    if (_dead_entities.empty())
        return Entity(_nb_entities++);
    Entity temp = _dead_entities.front();
    _dead_entities.pop_front();
    return temp;
}

inline auto ECS::entity_from_index(std::size_t idx) -> Entity
{
    return Entity(idx);
}


inline auto ECS::kill_entity(const Entity & entity) -> void
{
    for (auto &func : _freset_entity_components)
        func(entity);
    _dead_entities.push_back(entity);
}

template <typename Component>
auto ECS::add_component(Entity const & to, Component && c) -> typename SparseArray<Component >::reference_type
{
    SparseArray<Component> &temp = get_components<Component>();
    return temp.insert_at(to, c);
}

template <typename Component , typename ... Params >
auto ECS::emplace_component(Entity const & to, Params &&... p) -> typename SparseArray<Component>:: reference_type
{
    SparseArray<Component> &temp = get_components<Component>();
    return temp.emplace_at(to, p ...);
}

template <typename Component>
auto ECS::remove_component(Entity const & from) -> void
{
    SparseArray<Component> &temp = get_components<Component>();
    temp.erase(from);
    return;
}


template <class Event>
auto ECS::register_event () -> void
{
    auto type = std::type_index(typeid(Event));

    _events[type] = systems_type<Event>();
    return;
}
template <class Event >
auto ECS::get_events() -> systems_type < Event > &
{
    auto index = std::type_index(typeid(Event));
    return std::any_cast<systems_type<Event> &>(_events.at(index));
}

template <class Event >
auto ECS::get_events() const -> const systems_type < Event > &
{
    auto index = std::type_index(typeid(Event));
    return std::any_cast<const systems_type<Event> &>(_events.at(index));
}

template <class Event, class... Components, typename System>
auto ECS::subscribe(System &&system) -> void
{
    auto &events = get_events<Event>();
    events.push_back(std::forward<System>(system));
}

template <class Event>
auto ECS::post(const Event &event) -> void
{
    auto &events = get_events<Event>();
    _callback_pool.push_back([this, &events, &event]() {
        for (auto &system : events) {
            system(*this, event);
        }
    });
}

auto ECS::front(void) -> const callback_type &
{
    return _callback_pool.front();
}

auto ECS::pop_front(void) -> void
{
    _callback_pool.pop_front();
}

auto ECS::empty(void) const -> bool
{
    return _callback_pool.empty();
}
