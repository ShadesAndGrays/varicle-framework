#include "menu.hpp"

#include "engine/asset/raylib-asset.hpp"
#include "engine/core/engine-variant/engine-variant-property.hpp"
#include "engine/core/engine-variant/engine-variant.hpp"
#include "engine/core/service-locator.hpp"
#include "engine/ecs/components.hpp"
#include "engine/render/render-system.hpp"

#include <imgui.h>
#include <iostream>
#include <memory>

using namespace entt::literals;

void MenuScene::init() {
    using namespace varicle;
    ServiceLocator::provide(std::make_unique<RaylibAssetLoader>());

    auto &asset_loader = ServiceLocator::get<RaylibAssetLoader>();
    asset_loader.load_asset("assets/bird.png");
    auto x = asset_loader.get_reader().get_asset_list();
    for (auto i : x) {
        std::cout << i << std::endl;
    }

    auto e = registry.create();
    registry.emplace<components::GlobalTransform2D>(e, 650.0f, 150.0f,
                                                             1.0f, 0.0f);
    // registry.emplace<Position>(e, 650.0f, 150.0f);
    registry.emplace<components::Sprite>(e, "assets/bird.png", 0.0f, 0.f, 100.f,
                                         100.f, true, false, 0.f);
    auto img =
        LoadImageFromTexture(*asset_loader.get_texture("assets/bird.png"));
    SetWindowIcon(img);
    UnloadImage(img);

    auto &p_database = varicle::ServiceLocator::get<PropertyDatabase>();

    registry.emplace<varicle::components::LocalTransform2D>(e, 100.0f, 100.0f,
                                                            10.0f, 5.0f);

    EngineVariant current_pos =
        p_database.get_value(registry, e, "global_position"_hs);
    EngineVariant current_scale = p_database.get_value(registry, e, "scale"_hs);
    EngineVariant current_rot =
        p_database.get_value(registry, e, "rotation"_hs);

    std::cout << current_pos << current_scale << current_rot << std::endl;
}

void MenuScene::update(float dt) {}

void MenuScene::render() {
    varicle::update_render_system(registry);
    DrawCircleV({650, 400}, 100, PURPLE);
}

void MenuScene::ui() {

    // Get the current screen/viewport size
    ImVec2 screen_size = ImGui::GetIO().DisplaySize;

    // size of button container
    ImVec2 vbox_size = ImVec2(200.0f, 250.0f);

    // set next container to be center of the screen
    ImVec2 screen_center = ImVec2(screen_size.x * 0.5f, screen_size.y * 0.5f);
    ImGui::SetNextWindowPos(screen_center, ImGuiCond_Always,
                            ImVec2(0.5f, 0.5f));
    ImGui::SetNextWindowSize(vbox_size);

    // remove sub window decoration
    ImGuiWindowFlags flags =
        ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground;

    ImGui::Begin("VBoxContainer", nullptr, flags);

    // set button width to be size fill container
    ImVec2 button_size = ImVec2(ImGui::GetContentRegionAvail().x, 50.0f);

    // ImGui::SetCursorPos(centeredPos);
    if (ImGui::Button("Play", button_size)) {
        v::ServiceLocator::get<v::SceneManager>().switch_to_scene("main");
    }

    ImGui::Dummy(ImVec2(0, 10)); // Gap

    if (ImGui::Button("Quit", button_size)) {
        v::ServiceLocator::get<v::SceneManager>().quit();
    }

    ImGui::End();
}
