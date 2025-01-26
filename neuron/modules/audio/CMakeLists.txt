cmake_minimum_required(VERSION 3.30)
project(neuron_audio VERSION 0.1.0)

add_library(neuron_audio src/neuron/audio/audio.hpp src/neuron/audio/audio.cpp)
target_include_directories(neuron_audio PUBLIC src/)
target_link_libraries(neuron_audio PUBLIC neuron::core )
add_library(neuron::audio ALIAS neuron_audio)

Neuron_PrepModule(neuron_audio AUDIO neuron/audio)