cmake_minimum_required(VERSION 3.30)
project(neuron VERSION 0.1.0)

include(FetchContent)
include(cmake/NeuronModules.cmake)

add_library(neuron_all INTERFACE)
add_library(neuron::all ALIAS neuron_all)

Neuron_Setup()
add_subdirectory(modules)
Neuron_MakeDocsTarget()

target_link_libraries(neuron_all INTERFACE neuron::core neuron::log neuron::os neuron::application)

# Generated
target_link_libraries(neuron_all INTERFACE neuron::ecs)

# Generated
target_link_libraries(neuron_all INTERFACE neuron::audio)

# Generated
target_link_libraries(neuron_all INTERFACE neuron::ecs_application)
