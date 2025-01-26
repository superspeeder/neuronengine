#pragma once

#include "neuron/application/compile_mode.hpp"

namespace neuron::application {
    NEURON_APP_API int         version_major();
    NEURON_APP_API int         version_minor();
    NEURON_APP_API int         version_patch();
    NEURON_APP_API const char *version_string();

    class NEURON_APP_API Application {
      public:
        Application();
        virtual ~Application() = default;

        virtual void init()   = 0;
        virtual void create() = 0;
        virtual void update() = 0;
    };
} // namespace neuron::application
