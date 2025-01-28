#pragma once
#include "neuron/core/module_base.hpp"
#include "neuron/ecs/compile_mode.hpp"

#include <flecs.h>

namespace neuron::ecs {
    NEURON_ECS_API int         version_major();
    NEURON_ECS_API int         version_minor();
    NEURON_ECS_API int         version_patch();
    NEURON_ECS_API const char *version_str();

    class NEURON_ECS_API EcsManager {
      public:
        EcsManager(const EcsManager &other)                = delete;
        EcsManager(EcsManager &&other) noexcept            = default;
        EcsManager &operator=(const EcsManager &other)     = delete;
        EcsManager &operator=(EcsManager &&other) noexcept = default;

        EcsManager();

        [[nodiscard]] const flecs::world &world() const noexcept;

        inline const flecs::world &operator*() const noexcept { return m_World; };

        inline const flecs::world *operator->() const noexcept { return &m_World; };

        [[nodiscard]] flecs::untyped_component tag_component() const;
        [[nodiscard]] flecs::untyped_component sparse_tag_component() const;

        flecs::app_builder app();

      private:
        flecs::world m_World;
    };

    /**
     * @brief Base class which provides easy ways for modules to provide ECS support.
     *
     * You should still implement the standard module functions unless your functionality is exclusive to an ECS (in which case you should override those functions to throw a
     * std::logic_error, except for on_dispose, which is always called during program execution)
     */
    class NEURON_ECS_API EcsModuleBase : public ModuleBase {
      public:
        inline explicit EcsModuleBase(const std::string_view &name) : ModuleBase(name) {}

        /**
         * @brief Run during the ECS application configure_components step.
         *
         * @param ecs_manager
         * @see neuron::ecs_application::EcsApplication::configure_components
         */
        virtual void configure_components(const EcsManager &ecs_manager);

        /**
         * @brief Run at the end of the create step in an ECS application.
         *
         * @param ecs_manager
         * @see neuron::ecs_application::EcsApplication::create
         */
        virtual void initialize_system(const EcsManager &ecs_manager);
    };

    // neuron::ecs doesn't actually have its own module, since there is no real purpose for it since this module provides ways for modules to provide ecs support and for the user
    // to easily interact with the ecs system.
} // namespace neuron::ecs
