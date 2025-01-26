cmake_minimum_required(VERSION 3.30)
project(neuron_os VERSION 0.1.0)

add_library(neuron_os src/neuron/os/common/window.cpp src/neuron/os/common/window.hpp
        src/neuron/os/os.hpp
        src/neuron/os/os.cpp)
target_include_directories(neuron_os PUBLIC src/)
target_link_libraries(neuron_os PUBLIC neuron::core neuron::log)
add_library(neuron::os ALIAS neuron_os)

Neuron_PrepModule(neuron_os OS neuron/os)
