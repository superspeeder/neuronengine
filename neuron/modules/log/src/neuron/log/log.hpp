#pragma once

#include "neuron/log/compile_mode.hpp"

#include "neuron/ecs/ecs.hpp"

#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

namespace neuron::log {
    NEURON_LOG_API int         version_major();
    NEURON_LOG_API int         version_minor();
    NEURON_LOG_API int         version_patch();
    NEURON_LOG_API const char *version_str();

    enum class SimpleLoggerSink {
        STDOUT,
        PRIMARY_ROTATING_FILE,
        UNIQUE_ROTATING_FILE,
    };

    /**
     * @brief A simple form of logger configuration
     *
     * For the most part, you probably don't need much more than this for configuring your loggers. If you do, there is a full LoggerConfiguration struct you can use for ECS, with
     * much more complex rules (or in normal mode you would just use the various sink configurations to create the logger).
     *
     * @note In ECS mode, this is converted into a LoggerConfiguration and a set of SinkConfiguration and SinkComponent objects, which provides a
     * uniform interface for loggers.
     */
    struct SimpleLogger {
        std::string                   name;
        spdlog::level::level_enum     defaultLevel;
        bool                          ignoreGlobalLevelOverride;
        std::vector<SimpleLoggerSink> enabledSinks;
    };

    /**
     * @brief A basic logger configuration.
     *
     * This is used for some basic stuff about the logger which doesn't fit into the things needed to create a sink.
     *
     * @note ECS mode <b>only</b>
     */
    struct LoggerConfiguration {
        std::string               name;
        spdlog::level::level_enum defaultLevel;
    };

    /**
     * @brief A reference to the actual sink created (use this is if you need to create your own sinks).
     *
     * @note ECS mode <b>only</b>
     */
    struct SinkComponent {
        std::shared_ptr<spdlog::sinks::sink> sink;
    };

    /**
     * @brief ECS relationship for connecting loggers to external sinks.
     *
     * If you create an entity which has a SinkComponent (or get the system to create one by adding sink configurations to it), then you can use that entity as a sink in a logger
     * (allowing you to share sinks or even groups of sinks between loggers) by using this relationship type.
     *
     * @note ECS mode <b>only</b>
     */
    struct HasSink {};

    /**
     * @brief This allows the log level of a specific logger to be overridden.
     *
     * @note ECS mode <b>only</b>
     */
    struct LogLevelOverride {
        spdlog::level::level_enum level;
    };

    /**
     * @brief This allows for the log level to be overridden for all loggers at once
     *
     * Unlike the specific override, this only applies to loggers which aren't already set to a more granular level (i.e. a global override of info will not change a logger which
     * is already set to debug, however a global override of debug will change a logger set to info down to debug while it's active)
     *
     * The default global log level override is off (which means that no loggers will be overridden).
     *
     * @note ECS mode <b>only</b>
     */
    struct GlobalLogLevelOverride {
        spdlog::level::level_enum level;
    };

    /**
     * @brief This component holds a reference to the logger.
     *
     * The logging module will automatically make these when it sees entities which have logging configuration components but no actual logger.
     */
    struct LoggerComponent {
        std::shared_ptr<spdlog::logger> logger;
    };

    class NEURON_LOG_API LoggingModule : public ecs::EcsModuleBase {
      public:
        LoggingModule();
        ~LoggingModule() override;

        [[nodiscard]] int         version_major() const noexcept override;
        [[nodiscard]] int         version_minor() const noexcept override;
        [[nodiscard]] int         version_patch() const noexcept override;
        [[nodiscard]] const char *version_str() const noexcept override;

        void on_create() override;
        void on_dispose() override;
        void configure_components(const ecs::EcsManager &ecs_manager) override;
        void initialize_system(const ecs::EcsManager &ecs_manager) override;

        std::shared_ptr<spdlog::logger> create_logger(const SimpleLogger &logger);
        std::shared_ptr<spdlog::logger> create_logger(const LoggerConfiguration &configuration, const std::vector<std::shared_ptr<spdlog::sinks::sink>> &sinks);

      private:
        std::shared_ptr<spdlog::logger>                       m_PrimaryLogger;
        std::shared_ptr<spdlog::sinks::rotating_file_sink_mt> m_PrimaryFileSink;
        std::shared_ptr<spdlog::sinks::stdout_color_sink_mt>  m_PrimaryStdoutSink;

        flecs::entity &build_logger_cfg(flecs::entity &e, SimpleLogger &simple_logger);
        flecs::entity &build_logger(flecs::entity &e, LoggerConfiguration &logger_configuration);
    };

    namespace tags {
        extern NEURON_LOG_API flecs::untyped_component IgnoreGlobalLevelOverride;
    }

    namespace global {
        extern NEURON_LOG_API flecs::entity PrimaryLogger;
        extern NEURON_LOG_API std::weak_ptr<spdlog::logger> primary_logger;
    } // namespace global

    namespace sinks {
        extern NEURON_LOG_API flecs::entity PrimaryFileOutput;
        extern NEURON_LOG_API flecs::entity PrimaryStdout;
    } // namespace sinks
} // namespace neuron::log
