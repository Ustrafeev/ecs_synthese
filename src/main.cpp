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

int main(void)
{

    // step 0
    Entity test(5);
    std::cout<<test<<std::endl;

    // step 1
    SparseArray<int> array;
    array.emplace_at(1, 1);

    for (int i = 0; i < 6; i++) {
        std::cout << array[i].value_or(0) << std::endl;
    }

    // step 2

    ECS ecs;
    SparseArray<int> array2;

    ecs.register_component<int>().emplace_at(1, 1);
    array2 = ecs.get_components<int>();

    for (int i = 0; i < 6; i++) {
        std::cout << array2[i].value_or(5) << std::endl;
    }
    return 0;
}
