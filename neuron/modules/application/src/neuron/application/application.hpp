#pragma once

#include "neuron/application/compile_mode.hpp"

#include "neuron/core/module_base.hpp"

#include <optional>
#include <vector>
#include <memory>

namespace neuron::application {
    NEURON_APP_API int         version_major();
    NEURON_APP_API int         version_minor();
    NEURON_APP_API int         version_patch();
    NEURON_APP_API const char *version_string();

    struct ApplicationSettings {
        std::optional<float> targetFrameRate;
        std::unordered_set<std::shared_ptr<ModuleBase>> modules;
    };

    class NEURON_APP_API Application {
      public:
        explicit Application(ApplicationSettings settings = {});
        virtual ~Application();

        Application(const Application &other)                = delete;
        Application(Application &&other) noexcept            = default;
        Application &operator=(const Application &other)     = delete;
        Application &operator=(Application &&other) noexcept = default;

        virtual void create() = 0;
        virtual void update() = 0;

        /**
         * @brief Runs the application mainloop & manages setup, cleanup, and state
         * This <em>can</em> be overridden, however unless you need to change the logic of how an application runs (like the ecs_application module does), then you should avoid
         * touching this if at all possible.
         */
        virtual void run();


    protected:
        ApplicationSettings settings;
        std::vector<std::shared_ptr<ModuleBase>> modules;

        virtual void modules_create();
        virtual void modules_update();

        [[nodiscard]] virtual std::optional<const std::string_view> verify_module(const std::shared_ptr<ModuleBase> &module) const;

    private:
        void order_modules();
    };

    /// NOTE: there is no module for neuron::application because it would serve no purpose, as applications are designed to manage modules
} // namespace neuron::application
