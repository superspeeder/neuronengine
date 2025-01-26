#pragma once
#include "neuron/ecs_application/compile_mode.hpp"

#include <neuron/application/application.hpp>

namespace neuron::ecs_application {
    NEURON_ECS_APP_API int version_major();
    NEURON_ECS_APP_API int version_minor();
    NEURON_ECS_APP_API int version_patch();
    NEURON_ECS_APP_API const char* version_str();

    /**
     * @brief Extension to neuron::application::Application which is built around using an ECS, which has a much more scalable workflow than the base application does by default.
     */
    class NEURON_ECS_APP_API EcsApplication : public application::Application {

    };
}
