#include "neuron/ecs_application/ecs_application.hpp"

#include <stdexcept>

namespace neuron::ecs_application {
    int version_major() {
        return NEURON_ECS_APP_VERSION_MAJOR;
    }

    int version_minor() {
        return NEURON_ECS_APP_VERSION_MINOR;
    }

    int version_patch() {
        return NEURON_ECS_APP_VERSION_PATCH;
    }

    const char *version_str() {
        return NEURON_ECS_APP_VERSION;
    }

    EcsApplication::EcsApplication(const EcsApplicationSettings &ecs_settings, const application::ApplicationSettings &settings)
        : Application(settings), ecs_settings(ecs_settings) {}

    void EcsApplication::configure_components() {}

    void EcsApplication::setup() {}

    void EcsApplication::create() {
        configure_system_components();
        configure_components();
        setup();
        initialize_systems();
    }

    void EcsApplication::update() {
        throw std::logic_error("Not implemented (EcsApplication manages updates differently from )");
    }

    void EcsApplication::run() {
        create();

        auto app = m_ecs.app().ctx(this);
        if (settings.targetFrameRate.has_value()) {
            app.target_fps(settings.targetFrameRate.value());
        }

        app.run();
    }

    const flecs::world &EcsApplication::world() const noexcept {
        return m_ecs.world();
    }

    const ecs::EcsManager &EcsApplication::ecs() const noexcept {
        return m_ecs;
    }

    void EcsApplication::configure_system_components() const {
        for (const auto &module : modules) {
            if (const auto &ecs_module = std::dynamic_pointer_cast<ecs::EcsModuleBase>(module)) {
                ecs_module->configure_components(m_ecs);
            } else {
                throw std::logic_error("Cannot use non-ECS modules in an ECS application");
            }
        }
    }

    void EcsApplication::initialize_systems() const {
        for (const auto &module : modules) {
            if (const auto &ecs_module = std::dynamic_pointer_cast<ecs::EcsModuleBase>(module)) {
                ecs_module->initialize_system(m_ecs);
            } else {
                throw std::logic_error("Cannot use non-ECS modules in an ECS application");
            }
        }
    }
} // namespace neuron::ecs_application
