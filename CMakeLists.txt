cmake_minimum_required(VERSION 2.8)

project(karl)

link_directories(/home/krzysztof/Projects/moon-lang/build)

include_directories(
    /home/krzysztof/Projects/moon-lang
    ./utils
    ./state
    ./cam
    ./ent
    ./sys
    ./cmp
    ./res
    .
    )

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Werror -g -O0")

add_executable(karl
    ./Main.cpp
    ./sys/SysPhysics.cpp
    ./sys/SysDrawing.cpp
    ./cam/CamBound.cpp
    ./cam/CamFlying.cpp
    ./res/Resources.cpp
    ./res/ResShaderDebug.cpp
    ./res/ResShader.cpp
    ./Config.cpp
    ./ent/Ent.cpp
    ./cmp/CmpPhysicsSimple.cpp
    ./cmp/CmpApprDebug.cpp
    ./cmp/CmpPhysicsCar.cpp
    ./cmp/CmpPhysics.cpp
    ./state/StGame.cpp
    ./state/StGlPlay.cpp
    ./state/StMachine.cpp
    ./utils/GeomFac.cpp
    ./Platform.cpp
    ./Common.cpp
    )

target_link_libraries(karl moonlang allegro_monolith ode GL)
