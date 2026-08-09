#include "menu.hpp"

#include "engine/asset/raylib-asset.hpp"
#include "engine/core/engine-variant/engine-variant-property.hpp"
#include "engine/core/engine-variant/engine-variant.hpp"
#include "engine/core/service-locator.hpp"
#include "engine/ecs/components.hpp"
#include "engine/render/render-system.hpp"

#include <format>
#include <imgui.h>
#include <iostream>
#include <memory>

using namespace entt::literals;

entt::entity e;

void MenuScene::init() {
    using namespace varicle;
    // We provide an asset loader to the global context
    ServiceLocator::provide(std::make_unique<RaylibAssetLoader>());

    // Use asset_loader to load asset into memory from our data store
    auto &asset_loader = ServiceLocator::get<RaylibAssetLoader>();
    asset_loader.load_asset("assets/black-guy-spritesheet.png");

    // Uncomment to take a peak at the asset that can be loaded
    // auto x = asset_loader.get_reader().get_asset_list();
    // for (auto i : x) {
    //     std::cout << i << std::endl;
    // }

    e = registry.create();
    // add a sprite_component and transform components to have the sprite be
    // rendered
    SpriteUtil::add_sprite_component(registry, e,
                                     {"assets/black-guy-spritesheet.png", 0.0f,
                                      0.f, 100.f, 100.f, false, false, 0.f});
    SpriteUtil::add_animated_spirte_component(registry, e,
                                              {.cell_width = 16,
                                               .cell_height = 16,
                                               .h_cells = 2,
                                               .v_cells = 2,
                                               .total_frames = 4,
                                               .current_frame = 0

                                              });
    TransformUtil::add_transform_components(registry, e);
    TransformUtil::set_position(registry, e, Vec2{650.0f, 150.0f});

    // Just changing the window icon
    // auto img =
    //     LoadImageFromTexture(*asset_loader.get_texture("assets/bird.png"));
    // SetWindowIcon(img);
    // UnloadImage(img);
}

void MenuScene::deinit() {}

Rectangle
get_source_rect(const varicle::components::AnimatedSprite &animated_sprite);

void MenuScene::update(float dt) {
    if (IsKeyPressed(KEY_RIGHT)) {
        registry.get<varicle::components::AnimatedSprite>(e).current_frame++;
    }
    if (IsKeyPressed(KEY_LEFT)) {
        registry.get<varicle::components::AnimatedSprite>(e).current_frame--;
    }
}

void MenuScene::render() {
    using namespace varicle;
    RenderSystem::update_render_system(registry);
    TransformSystem::update_global_transform(registry);
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
