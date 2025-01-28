#include "module_base.hpp"

namespace neuron {
    ModuleBase::ModuleBase(const std::string_view name) : m_name(name) {}

    std::unordered_set<std::string> ModuleBase::get_dependencies() const noexcept {
        return {};
    }

    void ModuleBase::on_create() {}

    void ModuleBase::on_dispose() {}

    void ModuleBase::on_update() {}

    std::string ModuleBase::name() const noexcept {
        return m_name;
    }
} // neuron