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

namespace timer = std::chrono;
struct FrameEvent {
    FrameEvent(const timer::duration <float > & time_stamp);
    ~FrameEvent() = default ;
    timer::duration<float> _time_stamp ;
};

FrameEvent::FrameEvent(const timer::duration <float > & time_stamp) : _time_stamp(time_stamp) {};

struct QuitEvent {
    QuitEvent () = default ;
    ~ QuitEvent () = default ;
};

int main ( void )
{
    ECS ecs ;
    bool running = true ;
    unsigned int frame_counter = 0;
    ecs.register_event<FrameEvent>() ;
    ecs.register_event<QuitEvent>();
    ecs.subscribe<QuitEvent>([& running ]( ECS & , const QuitEvent &) -> void { running = false ; }) ;
    ecs.subscribe < FrameEvent >(
        []( ECS & , const FrameEvent &) -> void {
            std :: cout << " Frame !" << std :: endl ;
    }
    );
    const auto FPS = 10;
    const timer::duration <float , std :: ratio <1 , FPS > > frameRate (1) ;
    timer::time_point < timer :: steady_clock > current_time ;
    timer::time_point < timer :: steady_clock > previous_time (timer::steady_clock :: now () ) ;
    timer::duration <float > dtime = timer :: duration <float >:: zero () ;
    while ( running ) {
        current_time = timer :: steady_clock :: now () ;
        dtime += current_time - previous_time ;
        previous_time = current_time ;
        if ( frame_counter > 100) {
            ecs.post<QuitEvent>(QuitEvent()) ;
        }
        if (dtime >= frameRate ) {
            ecs.post<FrameEvent>(FrameEvent(dtime));
            ++ frame_counter ;
            dtime = std :: chrono :: duration <float >:: zero () ;
        }
        while (!ecs.empty()) {
            auto evt = ecs.front();
            evt();
            ecs.pop_front();
        }
    }
    return 0;
}
