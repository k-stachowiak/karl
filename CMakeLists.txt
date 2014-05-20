cmake_minimum_required(VERSION 2.8)

project(karl)

link_directories(/home/krzysztof/Projects/moon-lang/build)

include_directories(
    /home/krzysztof/Projects/moon-lang
    ./utils
    ./state
    ./ent
    ./sys
    ./cmp
    .
    )

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Werror -g -O0")

add_executable(karl
    ./Config.cpp
    ./Platform.cpp
    ./Common.cpp
    ./Resources.cpp
    ./Main.cpp
    ./cmp/CmpAppearance.cpp
    ./cmp/CmpPhysics.cpp
    ./cmp/CmpPhysicsSimple.cpp
    ./cmp/CmpPhysicsCar.cpp
    ./ent/Ent.cpp
    ./sys/CameraFlying.cpp
    ./sys/SysPhysics.cpp
    ./sys/SysDrawing.cpp
    ./state/StateGame.cpp
    ./state/StateMachine.cpp
    )

target_link_libraries(karl moonlang allegro_monolith ode GL)
