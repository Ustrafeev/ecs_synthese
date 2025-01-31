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
#include "Entity.hpp"
#include <functional>
#include <list>

class ECS {
    public :
        using freset_type = std::function<void(const Entity &)>;
        using callback_type = std :: function < void ( void ) >;
        template <class Event >
        using system_type = std :: function < void ( ECS & , const Event &) >;
        template <class Event >
        using systems_type = std :: vector < system_type < Event > >;
        using event_type = std :: any ;
    public :
        ECS () ;
        ~ECS () = default ;
        template <class Component >
        auto register_component () -> SparseArray < Component > &;

        template <class Component >
        auto get_components () -> SparseArray < Component > &;

        template <class Component >
        auto get_components () const -> const SparseArray < Component > &;
        auto spawn_entity() -> Entity ;
        auto entity_from_index ( std :: size_t idx ) -> Entity ;
        auto kill_entity ( const Entity & entity ) -> void ;

        template <typename Component >
        auto add_component ( Entity const & to , Component && c ) ->
        typename SparseArray < Component >:: reference_type ;

        template <typename Component , typename ... Params >
        auto emplace_component ( Entity const & to , Params &&... p ) ->
            typename SparseArray < Component >:: reference_type ;

        template <typename Component> auto remove_component (Entity const & from) -> void;



        template <class Event > auto register_event () -> void ;
        template <class Event > auto get_events () -> systems_type < Event > &;
        template <class Event >
        auto get_events () const -> const systems_type < Event > &;
        template <class Event , class ... Components , typename System >
        auto subscribe ( System && system ) -> void ;
        template <class Event , class ... Components , typename System >
        auto subscribe ( System & system ) -> void ;
        template <class Event , class ... Components , typename System >
        auto subscribe ( const System & system ) -> void ;
        template <class Event >
        auto post ( const Event & event ) -> void ;
        auto front ( void ) -> const callback_type &;
        auto pop_front ( void ) -> void ;
        auto empty ( void ) const -> bool ;

    private :
        std::size_t _nb_entities;
        std::unordered_map<std::type_index, std::any>_components_arrays ;
        std::list<Entity> _dead_entities;
        std::vector<freset_type> _freset_entity_components ;
        std::unordered_map<std::type_index,event_type>_events ;
        std::list<callback_type>_callback_pool;


};


#include "Ecs.inl"