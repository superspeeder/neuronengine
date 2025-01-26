#include "log.hpp"

namespace neuron::log {
    int version_major() {
        return NEURON_LOG_VERSION_MAJOR;
    }

    int version_minor() {
        return NEURON_LOG_VERSION_MINOR;
    }

    int version_patch() {
        return NEURON_LOG_VERSION_PATCH;
    }

    const char *version_str() {
        return NEURON_LOG_VERSION;
    }

    void setup_default_logger() {}
} // namespace neuron::log
