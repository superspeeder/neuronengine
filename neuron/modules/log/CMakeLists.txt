cmake_minimum_required(VERSION 3.30)
project(neuron_log VERSION 0.1.0)

FetchContent_Declare(spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG v1.15.0
)

set(SPDLOG_USE_STD_FORMAT ON)
if (BUILD_SHARED_LIBS)
    set(SPDLOG_BUILD_SHARED ON)
endif()


FetchContent_MakeAvailable(spdlog)

add_library(neuron_log src/neuron/log/log.cpp src/neuron/log/log.hpp)
target_include_directories(neuron_log PUBLIC src/)
target_link_libraries(neuron_log PUBLIC spdlog::spdlog neuron::core)
add_library(neuron::log ALIAS neuron_log)

Neuron_PrepModule(neuron_log LOG neuron/log)
