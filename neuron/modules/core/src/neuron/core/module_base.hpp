#pragma once

#include "neuron/core/compile_mode.hpp"

#include <string>
#include <string_view>
#include <unordered_set>

namespace neuron {

    class NEURON_CORE_API ModuleBase {
      public:
        explicit ModuleBase(std::string_view name);
        virtual ~ModuleBase() = default;

        [[nodiscard]] virtual std::unordered_set<std::string> get_dependencies() const noexcept;

        virtual void on_create();
        virtual void on_dispose();
        virtual void on_update();

        [[nodiscard]] virtual int         version_major() const noexcept = 0;
        [[nodiscard]] virtual int         version_minor() const noexcept = 0;
        [[nodiscard]] virtual int         version_patch() const noexcept = 0;
        [[nodiscard]] virtual const char *version_str() const noexcept   = 0;

        [[nodiscard]] std::string name() const noexcept;

      private:
        std::string m_name;
    };

} // namespace neuron
