#include "main.hpp"

#include "engine/core/color.hpp"
#include "engine/ecs/components.hpp"
#include "engine/render/render-system.hpp"

#include <format>
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

    auto p = create_named_entity(registry, "parent");
    auto c1 = create_named_entity(registry, "child1");
    auto c2 = create_named_entity(registry, "child2");
    Hierachy::set_parent(registry, c1, p);
    Hierachy::set_parent(registry, c2, p);

    auto *children_component = registry.try_get<components::Children>(p);
    std::cout << "Children of " << registry.get<Name>(p).name << std::endl;

    SpriteUtil::add_sprite_component(registry, p, {.texture_path = ""});
    SpriteUtil::add_tint_component(registry, p, {varicle::Color::Red()});
    TransformUtil::add_transform_components(registry, p);
    TransformUtil::set_position(registry, p, EngineVariant(Vec2{300, 300}));

    SpriteUtil::add_sprite_component(registry, c1, {.texture_path = ""});
    SpriteUtil::add_tint_component(registry, c1, {varicle::Color::Orange()});
    registry.get<components::LocalTransform2D>(c1).position = {100, 100};

    SpriteUtil::add_sprite_component(registry, c2, {.texture_path = ""});
    SpriteUtil::add_tint_component(registry, c2, {varicle::Color::Yellow()});
    registry.get<components::GlobalTransform2D>(c2).position = {200, 200};

    // for (auto child : children_component->children) {
    //     std::cout << registry.get<Name>(child).name << std::endl;
    // }
}

void MainScene::deinit() {}

void MainScene::update(float dt) {
    varicle::TransformSystem::update_global_transform(registry);
}

void MainScene::render() {
    varicle::RenderSystem::update_render_system(registry);
}

std::string get_name(entt::registry &registry, entt::entity entity) {
    std::string name =
        "Entity " + std::to_string(static_cast<uint32_t>(entity));

    if (auto *name_component = registry.try_get<Name>(entity)) {
        name = std::format("{}", name_component->name);
    }

    return name;
}

void MainScene::ui() {
    auto &entites = registry.storage<entt::entity>();
    ImGui::Begin("ECS Registry Inspector");

    for (auto entityId : entites) {
        std::string label = get_name(registry, entityId);

        if (ImGui::TreeNode(label.c_str())) {

            // Inspect Transform component if attached
            if (auto *global_transform =
                    registry.try_get<v::components::GlobalTransform2D>(
                        entityId)) {
                if (ImGui::TreeNode("Global Transform Component")) {
                    ImGui::DragFloat2("Position",
                                      &global_transform->position.x);
                    ImGui::DragFloat("Rotation", &global_transform->rotation,
                                     0.1f);
                    ImGui::DragFloat("Scale", &global_transform->scale, 0.1f);
                    ImGui::TreePop();
                }
            }

            if (auto *local_transform =
                    registry.try_get<v::components::LocalTransform2D>(
                        entityId)) {
                if (ImGui::TreeNode("Local Transform Component")) {
                    ImGui::DragFloat2("Position", &local_transform->position.x);
                    ImGui::DragFloat("Rotation", &local_transform->rotation,
                                     0.1f);
                    ImGui::DragFloat("Scale", &local_transform->scale, 0.1f);
                    ImGui::TreePop();
                }
            }

            if (auto *children_component =
                    registry.try_get<v::components::Children>(entityId)) {
                if (ImGui::TreeNode("Children Component")) {
                    for (auto child : children_component->children) {
                        ImGui::Text("%s", get_name(registry, child).c_str());
                    }
                    ImGui::TreePop();
                }
            }

            // Inspect Health component if attached
            // if (auto *health = registry.try_get<Health>(entityId)) {
            //     if (ImGui::TreeNode("Health Component")) {
            //         ImGui::SliderInt("HP", &health->current, 0, health->max);
            //         ImGui::TreePop();
            //     }
            // }

            ImGui::TreePop();
        }
    }

    ImGui::End();
}
