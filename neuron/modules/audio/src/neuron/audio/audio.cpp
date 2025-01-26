#include "neuron/audio/audio.hpp"

namespace neuron::audio {
    int version_major() {
        return NEURON_AUDIO_VERSION_MAJOR;
    }

    int version_minor() {
        return NEURON_AUDIO_VERSION_MINOR;
    }

    int version_patch() {
        return NEURON_AUDIO_VERSION_PATCH;
    }

    const char *version_str() {
        return NEURON_AUDIO_VERSION;
    }
}