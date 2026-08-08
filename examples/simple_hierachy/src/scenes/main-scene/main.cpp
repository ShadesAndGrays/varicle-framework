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
    // ServiceLocator::provide(std::make_unique<RaylibAssetLoader>());

    auto p = create_named_entity(registry, "parent");
    auto c1 = create_named_entity(registry, "child1");
    auto c2 = create_named_entity(registry, "child2");
    Hierachy::set_parent(registry, c1, p);
    Hierachy::set_parent(registry, c2, p);

    auto *children_component = registry.try_get<components::Children>(p);
    std::cout << "Children of " << registry.get<Name>(p).name << std::endl;

    registry.emplace_or_replace<components::Sprite>(c1) = {
        "", 0, 0, 100, 100, false, false, 0};

    registry.emplace<components::GlobalTransform2D>(c1) = {{100, 100}, 1, 0};

    for (auto child : children_component->children) {
        std::cout << registry.get<Name>(child).name << std::endl;
    }
}

void MainScene::update(float dt) {}

void MainScene::render() { varicle::update_render_system(registry); }

void MainScene::ui() {}
