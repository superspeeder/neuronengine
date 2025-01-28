cmake_minimum_required(VERSION 3.30)
project(neuron_core VERSION 0.1.0)

add_library(neuron_core src/neuron/wrappers/stbi_wrapper.cpp src/neuron/wrappers/stbi_wrapper.hpp stb/stb_image.h
        src/neuron/core/core.cpp
        src/neuron/core/core.hpp
        src/neuron/core/module_base.cpp
        src/neuron/core/module_base.hpp
        src/neuron/core/dependency_graph.hpp)
target_include_directories(neuron_core PUBLIC src/)
target_include_directories(neuron_core PRIVATE stb/)
add_library(neuron::core ALIAS neuron_core)

Neuron_PrepModule(neuron_core CORE neuron/core)
