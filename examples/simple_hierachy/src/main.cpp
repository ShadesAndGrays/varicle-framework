#include "scenes/main-scene/main.hpp"
#include "engine/core/application.hpp"
#include "engine/core/service-locator.hpp"
#include "engine/scene/scene.hpp"

#include "scenes/menu-scene/menu.hpp"

#include <entt/entt.hpp>
#include <raylib.h>

class Game : public varicle::Application {

  public:
    void on_init() override {
        auto &scene_manager =
            varicle::ServiceLocator::get<varicle::SceneManager>();
        scene_manager.register_scene(
            "menu", []() { return std::make_unique<MenuScene>(); });

        scene_manager.register_scene(
            "main", []() { return std::make_unique<MainScene>(); });

        change_scene("main");
    }

    void on_shutdown() override {}
};

int main() {
    Game game;
    game.run();
    return 0;
}
