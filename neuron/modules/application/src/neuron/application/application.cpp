#include "application.hpp"

namespace neuron::application {
    int version_major() {
        return NEURON_APP_VERSION_MAJOR;
    }

    int version_minor() {
        return NEURON_APP_VERSION_MINOR;
    }

    int version_patch() {
        return NEURON_APP_VERSION_PATCH;
    }

    const char *version_string() {
        return NEURON_APP_VERSION;
    }

    Application::Application() = default;
}
