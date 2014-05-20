cmake_minimum_required(VERSION 2.8)

project(karl)

link_directories(/home/krzysztof/Projects/moon-lang/build)
include_directories(. ./cmp ./efwk ./utils ./state /home/krzysztof/Projects/moon-lang)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Werror -g -O0")

add_executable(karl
    ./config.cpp
    ./platform.cpp
    ./common.cpp
    ./resources.cpp
    ./main.cpp
    ./cmp/CmpAppearance.cpp
    ./cmp/CmpPhysics.cpp
    ./cmp/CmpPhysicsSimple.cpp
    ./cmp/CmpPhysicsCar.cpp
    ./efwk/sys_physics.cpp
    ./efwk/sys_drawing.cpp
    ./efwk/ent.cpp
    ./state/state_game.cpp
    ./state/machine.cpp)

target_link_libraries(karl moonlang allegro_monolith ode GL)
