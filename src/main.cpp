/*
** EPITECH PROJECT, 2024
** synthese
** File description:
** main.cpp
*/

#include "Entity.hpp"
#include "SparseArray.hpp"
#include <iostream>
#include "Ecs.hpp"
#include "Position.hpp"
#include <chrono>
#include "Entity.hpp"
#include "Position.hpp"
#include "Zipper.hpp"
#include "ZipperIt.hpp"
#include <iostream>
#include <chrono>

// void logging_system ( ECS &r ,
//     SparseArray < component :: position > const & positions ,
//     SparseArray < component :: velocity > const & velocities )
// {
//     for ( size_t i = 0; i < positions . size () && i < velocities . size () ; ++ i ) {
//         auto const & pos = positions [ i ];
//         auto const & vel = velocities [ i ];
//         if ( pos && vel ) {
//             std :: cerr << i << " : Position = { " << pos . value () . x << ", "
//             << pos . value () . y << " } , Velocity = { "
//             << vel . value () . vx << ", " << vel . value () . vy << " }"
//             << std :: endl ;
//         }
//     }
// }

// void logging_system ( ECS &r ,
// SparseArray < component :: position > const & positions ,
// SparseArray < component :: velocity > const & velocities )
// {
//     for ( auto &&[ i , pos , vel ]:Zipper(positions , velocities ) )
//     std :: cerr << i << ": Position = { " << pos.value() . x << ", " << pos.value() . y
//     << " } , Velocity = { " << vel.value().vx << ", " << vel.value().vy << " }" <<
//     std :: endl ;
// }

// int main(void)
// {

//     // step 0
//     Entity test(5);
//     std::cout<<test<<std::endl;

//     // step 1
//     SparseArray<int> array;
//     array.emplace_at(1, 1);

//     /*for (int i = 0; i < 6; i++) {
//         std::cout << array[i].value_or(0) << std::endl;
//     }*/

//     // step 2

//     ECS ecs;
//     SparseArray<int> array2;
//     Entity e = ecs.spawn_entity();
//     ecs.register_component<int>();

//     ecs.register_component<component::position>();
//     component::position p;
//     ecs.add_component<component::position>(e, std::move(p));
//     ecs.register_component<component::velocity>();
//     ecs.emplace_component<component::velocity>(e);

//     // ecs.add_component<int>(e, 1);

//         // array2 = ecs.get_components<int>();

//     // for (int i = 0; i < 6; i++) {
//     //     std::cout << array2[i].value_or(5) << std::endl;
//     // }
//     logging_system( ecs);
//     return 0;
// }

struct LoggingEvent {
    LoggingEvent() = default;
    ~LoggingEvent() = default;
};

void logging_system(ECS &, const LoggingEvent &, SparseArray<Component::Position> const &positions, SparseArray<Component::Velocity> const &velocities)
{
    for (auto &&[i, pos, vel] : Zipper(positions, velocities))
        std::cerr << i << ": Position = { " << pos.x << ", " << pos.y
            << " }, Velocity = { " << vel.vx << ", " << vel.vy << " } " <<
            std::endl;
}

int main(void)
{
    ECS ecs;
    Entity e;
    Component::Position pos;
    Component::Velocity vel;

    pos.x = 30;
    pos.y = 0;
    vel.vx = 1;
    vel.vy = 1;

    ecs.register_component<Component::Position>();
    ecs.register_component<Component::Velocity>();
    e = ecs.spawn_entity();

    ecs.add_component<Component::Position>(e, std::move(pos));
    ecs.emplace_component<Component::Velocity>(e);

    ecs.register_event<LoggingEvent>();
    ecs.subscribe<LoggingEvent, Component::Position, Component::Velocity>(std::move(logging_system));

    ecs.post<LoggingEvent>(LoggingEvent());

    while (!ecs.empty()) {
        auto evt = ecs.front();
        evt();
        ecs.pop_front();
    }
    return 0;
}