#include "menu.hpp"

#include "engine/core/service-locator.hpp"
#include "raylib.h"

#include <imgui.h>

void MenuScene::init() {}

void MenuScene::update(float dt) {}

void MenuScene::render() {}

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
