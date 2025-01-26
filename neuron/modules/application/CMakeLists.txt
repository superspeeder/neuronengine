cmake_minimum_required(VERSION 3.30)
project(neuron_application VERSION 0.1.0)

add_library(neuron_application src/neuron/application/application.cpp src/neuron/application/application.hpp)
target_include_directories(neuron_application PUBLIC src/)
target_link_libraries(neuron_application PUBLIC neuron::core neuron::log neuron::os)
add_library(neuron::application ALIAS neuron_application)

Neuron_PrepModule(neuron_application APP neuron/application)
