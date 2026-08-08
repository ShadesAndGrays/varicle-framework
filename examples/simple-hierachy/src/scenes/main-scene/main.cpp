#include "main.hpp"

#include "engine/ecs/components.hpp"
#include "engine/render/render-system.hpp"

#include <imgui.h>
#include <iostream>

using namespace entt::literals;

struct Name {
    std::string name;
};

entt::entity create_named_entity(entt::registry &registry,
                                 const std::string &p_name = "") {
    auto entity = registry.create();
    registry.emplace_or_replace<Name>(entity, p_name);
    return entity;
}

void MainScene::init() {
    using namespace varicle;

    auto player = create_named_entity(registry, "player");
}

void MainScene::deinit() {}

void MainScene::update(float dt) {}

void MainScene::render() {
    varicle::RenderSystem::update_render_system(registry);
}

void MainScene::ui() {}
