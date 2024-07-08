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

void logging_system(ECS & r)
{
    // std::
    auto const & positions = r.get_components<component::position>() ;
    auto const & velocities = r.get_components<component::velocity>() ;
    std::cout<<positions.size()<<std::endl;
    std::cout<<velocities.size()<<std::endl;
    for ( size_t i = 0; i < positions.size() && i < velocities.size(); ++i) {
        auto const &pos = positions[i];
        auto const &vel = velocities[i];
        if (pos && vel) {
            std :: cerr << i << ": Position = { " << pos.value().x << ", "
            << pos.value().y << " } , Velocity = { "
            << vel.value().vx << ", " << vel.value().vy << " }"
            << std::endl ;
        }
    }
}

int main(void)
{

    // step 0
    Entity test(5);
    std::cout<<test<<std::endl;

    // step 1
    SparseArray<int> array;
    array.emplace_at(1, 1);

    /*for (int i = 0; i < 6; i++) {
        std::cout << array[i].value_or(0) << std::endl;
    }*/

    // step 2

    ECS ecs;
    SparseArray<int> array2;
    Entity e = ecs.spawn_entity();
    ecs.register_component<int>();

    ecs.register_component<component::position>();
    component::position p;
    ecs.add_component<component::position>(e, std::move(p));
    ecs.register_component<component::velocity>();
    ecs.emplace_component<component::velocity>(e);

    // ecs.add_component<int>(e, 1);

        // array2 = ecs.get_components<int>();

    // for (int i = 0; i < 6; i++) {
    //     std::cout << array2[i].value_or(5) << std::endl;
    // }
    logging_system( ecs);
    return 0;
}
