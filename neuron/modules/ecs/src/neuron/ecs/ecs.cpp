#include "neuron/ecs/ecs.hpp"

namespace neuron::ecs {
    int version_major() {
        return NEURON_ECS_VERSION_MAJOR;
    }

    int version_minor() {
        return NEURON_ECS_VERSION_MINOR;
    }

    int version_patch() {
        return NEURON_ECS_VERSION_PATCH;
    }

    const char *version_str() {
        return NEURON_ECS_VERSION;
    }

    EcsManager::EcsManager() = default;

    const flecs::world &EcsManager::world() const noexcept {
        return m_World;
    }

    flecs::untyped_component EcsManager::tag_component() const {
        return m_World.component();
    }

    flecs::untyped_component EcsManager::sparse_tag_component() const {
        const flecs::untyped_component component = tag_component();
        component.add(flecs::Sparse);
        return component;
    }

    flecs::app_builder EcsManager::app() {
        return m_World.app();
    }

    void EcsModuleBase::configure_components(const EcsManager &ecs_manager) {}

    void EcsModuleBase::initialize_system(const EcsManager &ecs_manager) {}
} // namespace neuron::ecs
