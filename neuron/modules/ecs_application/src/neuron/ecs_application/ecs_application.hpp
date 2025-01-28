#pragma once
#include "neuron/ecs_application/compile_mode.hpp"

#include <neuron/application/application.hpp>

#include <flecs.h>
#include <neuron/ecs/ecs.hpp>

namespace neuron::ecs_application {
    NEURON_ECS_APP_API int         version_major();
    NEURON_ECS_APP_API int         version_minor();
    NEURON_ECS_APP_API int         version_patch();
    NEURON_ECS_APP_API const char *version_str();

    struct EcsApplicationSettings {};

    /**
     * @brief Extension to neuron::application::Application which is built around using an ECS, which has a much more scalable workflow than the base application does by default.
     *
     * When overriding EcsApplication::create, always call EcsApplication::create first before your code to ensure that the world is in the correct state (this is when the system
     * components and required things are set up, as well as where the user is allowed to set up their own components.
     */
    class NEURON_ECS_APP_API EcsApplication : public application::Application {
      public:
        explicit EcsApplication(const EcsApplicationSettings &ecs_settings = {}, const application::ApplicationSettings &settings = {});
        ~EcsApplication() override = default;

        virtual void configure_components();

        /**
         * @brief You should put any code that runs after component configuration and before system initialization (when certain important things resources might be initialized
         * like the render device or the windows) in here.
         */
        virtual void setup();

        void create() override;

        /**
         * @brief update cannot be overridden past EcsApplication as that goes against the idea of the system.
         */
        void update() final;

        void run() override;

        [[nodiscard]] const flecs::world &world() const noexcept;

        [[nodiscard]] const ecs::EcsManager &ecs() const noexcept;

      protected:
        EcsApplicationSettings ecs_settings;

      private:
        ecs::EcsManager m_ecs;

        void configure_system_components() const;
        void initialize_systems() const;
    };
} // namespace neuron::ecs_application
