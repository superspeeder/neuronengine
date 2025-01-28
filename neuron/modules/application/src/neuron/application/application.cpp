#include "application.hpp"

#include "neuron/core/dependency_graph.hpp"

#include <stdexcept>
#include <unordered_map>
#include <utility>

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

    Application::Application(ApplicationSettings settings) : settings(std::move(settings)) {
        order_modules();
    }

    Application::~Application() {
        for (const auto &module : modules) {
            module->on_dispose();
        }
    }

    void Application::run() {
        throw std::logic_error("Not implemented");
    }

    void Application::modules_create() {
        for (const auto &module : modules) {
            module->on_update();
        }
    }

    void Application::modules_update() {
        for (const auto &module : modules) {
            module->on_update();
        }
    }

    std::optional<const std::string_view> Application::verify_module(const std::shared_ptr<ModuleBase> &module) const {
        return std::nullopt;
    }

    void Application::order_modules() {
        if (settings.modules.empty())
            return;

        std::unordered_map<std::string, std::shared_ptr<ModuleBase>> modules_by_name;
        for (const auto &module : settings.modules) {
            modules_by_name[module->name()] = module;
        }

        DependencyGraph<std::string> dependency_graph;

        for (const auto &module : settings.modules) {
            dependency_graph.add_dependencies(module->name(), module->get_dependencies());
        }

        modules.reserve(settings.modules.size());
        for (const auto names = dependency_graph.generate_order(); const auto &module : names) {
            if (modules_by_name.contains(module)) {
                modules.push_back(modules_by_name[module]);
            } else {
                throw std::logic_error("Missing module dependency: " + module);
            }
        }
    }
} // namespace neuron::application
