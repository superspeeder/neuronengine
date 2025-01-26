cmake_minimum_required(VERSION 3.30)
project(neuron_ecs_application VERSION 0.1.0)

add_library(neuron_ecs_application src/neuron/ecs_application/ecs_application.hpp src/neuron/ecs_application/ecs_application.cpp)
target_include_directories(neuron_ecs_application PUBLIC src/)
target_link_libraries(neuron_ecs_application PUBLIC neuron::core neuron::application neuron::ecs)
add_library(neuron::ecs_application ALIAS neuron_ecs_application)

Neuron_PrepModule(neuron_ecs_application ECS_APP neuron/ecs_application)