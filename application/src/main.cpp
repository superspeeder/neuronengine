#include "neuron/core/dependency_graph.hpp"


#include <iostream>

#include <neuron/ecs_application/ecs_application.hpp>
#include <ostream>

flecs::untyped_component tag;

class FakeModule1 : public neuron::ecs::EcsModuleBase {
  public:
    FakeModule1() : EcsModuleBase("fake1") {}

    void configure_components(const neuron::ecs::EcsManager &ecs_manager) override { std::cout << "FakeModule1::configure_components" << std::endl; }

    [[nodiscard]] int version_major() const noexcept override { return 0; }

    [[nodiscard]] int version_minor() const noexcept override { return 0; }

    [[nodiscard]] int version_patch() const noexcept override { return 0; }

    [[nodiscard]] const char *version_str() const noexcept override { return "0.0.0"; }
};

class FakeModule2 : public neuron::ecs::EcsModuleBase {
  public:
    FakeModule2() : EcsModuleBase("fake2") {}

    void configure_components(const neuron::ecs::EcsManager &ecs_manager) override { std::cout << "FakeModule2::configure_components" << std::endl; }

    [[nodiscard]] std::unordered_set<std::string> get_dependencies() const noexcept override { return {"fake1", "fake3"}; }

    [[nodiscard]] int version_major() const noexcept override { return 0; }

    [[nodiscard]] int version_minor() const noexcept override { return 0; }

    [[nodiscard]] int version_patch() const noexcept override { return 0; }

    [[nodiscard]] const char *version_str() const noexcept override { return "0.0.0"; }
};

class FakeModule3 : public neuron::ecs::EcsModuleBase {
  public:
    FakeModule3() : EcsModuleBase("fake3") {}

    void configure_components(const neuron::ecs::EcsManager &ecs_manager) override { std::cout << "FakeModule3::configure_components" << std::endl; }

    [[nodiscard]] std::unordered_set<std::string> get_dependencies() const noexcept override { return {"fake1"}; }

    [[nodiscard]] int version_major() const noexcept override { return 0; }

    [[nodiscard]] int version_minor() const noexcept override { return 0; }

    [[nodiscard]] int version_patch() const noexcept override { return 0; }

    [[nodiscard]] const char *version_str() const noexcept override { return "0.0.0"; }
};

class TestApplication final : public neuron::ecs_application::EcsApplication {
  public:
    TestApplication()
        : EcsApplication({},
                         {.modules = {
                              std::make_shared<FakeModule1>(),
                              std::make_shared<FakeModule2>(),
                              std::make_shared<FakeModule3>(),
                          }}) {}

    void configure_components() override { tag = world().component(); }

    void create() override {
        EcsApplication::create();

        const auto &w = world();
        w.entity().add(tag);
        std::cout << "running" << std::endl;

        w.system("Test").kind(flecs::OnUpdate).with(tag).each([](flecs::entity e) {
            std::cout << "Hi!!!" << std::endl;
            e.world().quit();
        });
    }
};

int main() {
    try {
        TestApplication app;
        app.run();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }
    return 0;
}
