cmake_minimum_required(VERSION 3.30)
project(neuron_ecs VERSION 0.1.0)

FetchContent_Declare(flecs
        GIT_REPOSITORY "https://github.com/SanderMertens/flecs.git"
        GIT_TAG v4.0.4
)

FetchContent_MakeAvailable(flecs)

add_library(neuron_ecs src/neuron/ecs/ecs.hpp src/neuron/ecs/ecs.cpp)
target_include_directories(neuron_ecs PUBLIC src/)
target_link_libraries(neuron_ecs PUBLIC neuron::core $<IF:$<BOOL:BUILD_SHARED_LIBS>,flecs::flecs,flecs::flecs_static>)
add_library(neuron::ecs ALIAS neuron_ecs)

Neuron_PrepModule(neuron_ecs ECS neuron/ecs)