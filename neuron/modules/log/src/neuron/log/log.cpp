#include "log.hpp"

namespace neuron::log {
    namespace tags {
        flecs::untyped_component IgnoreGlobalLevelOverride;
    }

    namespace global {
        flecs::entity                 PrimaryLogger;
        std::weak_ptr<spdlog::logger> primary_logger;
    } // namespace global

    namespace sinks {
        flecs::entity PrimaryFileOutput;
        flecs::entity PrimaryStdout;
    } // namespace sinks

    int version_major() {
        return NEURON_LOG_VERSION_MAJOR;
    }

    int version_minor() {
        return NEURON_LOG_VERSION_MINOR;
    }

    int version_patch() {
        return NEURON_LOG_VERSION_PATCH;
    }

    const char *version_str() {
        return NEURON_LOG_VERSION;
    }

    LoggingModule::LoggingModule() : EcsModuleBase("neuron::log") {}

    LoggingModule::~LoggingModule() {
        spdlog::shutdown();
    }

    int LoggingModule::version_major() const noexcept {
        return NEURON_LOG_VERSION_MAJOR;
    }

    int LoggingModule::version_minor() const noexcept {
        return NEURON_LOG_VERSION_MINOR;
    }

    int LoggingModule::version_patch() const noexcept {
        return NEURON_LOG_VERSION_PATCH;
    }

    const char *LoggingModule::version_str() const noexcept {
        return NEURON_LOG_VERSION;
    }

    void LoggingModule::on_create() {}

    void LoggingModule::on_dispose() {}

    void LoggingModule::configure_components(const ecs::EcsManager &ecs_manager) {
        tags::IgnoreGlobalLevelOverride = ecs_manager.sparse_tag_component();
        // TODO: make log level overrides work

        // while this is not a component configuration, setting singletons here isn't problematic (and allows the user to properly work with the system).
        ecs_manager.world().set(GlobalLogLevelOverride{spdlog::level::off});

        // while these aren't components either, this is also ok since these are needed for setup.
        sinks::PrimaryFileOutput = ecs_manager.world().entity().emplace<SinkComponent>(m_PrimaryFileSink);
        sinks::PrimaryStdout     = ecs_manager.world().entity().emplace<SinkComponent>(m_PrimaryStdoutSink);
    }

    void LoggingModule::initialize_system(const ecs::EcsManager &ecs_manager) {}

    std::shared_ptr<spdlog::logger> LoggingModule::create_logger(const SimpleLogger &logger) {
        throw std::logic_error("not implemented");
    }

    std::shared_ptr<spdlog::logger> LoggingModule::create_logger(const LoggerConfiguration &configuration, const std::vector<std::shared_ptr<spdlog::sinks::sink>> &sinks) {
        throw std::logic_error("not implemented");
    }

    flecs::entity &LoggingModule::build_logger_cfg(flecs::entity &e, SimpleLogger &simple_logger) {
        throw std::logic_error("not implemented");
    }

    flecs::entity &LoggingModule::build_logger(flecs::entity &e, LoggerConfiguration &logger_configuration) {
        throw std::logic_error("not implemented");
    }
} // namespace neuron::log
