cmake_minimum_required(VERSION 3.30)
project(neuronengine)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (NOT EXISTS BUILD_SHARED_LIBS)
    set(BUILD_SHARED_LIBS ON)
endif()

add_subdirectory(neuron)
add_subdirectory(application)
