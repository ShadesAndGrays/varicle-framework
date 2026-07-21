#include "engine/core/application.hpp"
#include "engine/core/service-locator.hpp"
#include "engine/scene/scene.hpp"

#include "game/scenes/game-over-scene/game-over.hpp"
#include "game/scenes/main-scene/main-scene.hpp"
#include "game/scenes/menu-scene/menu.hpp"

#include <raylib.h>

class Game : public varicle::Application {

  public:
    void on_init() override {
        auto &scene_manager =
            varicle::ServiceLocator::get<varicle::SceneManager>();
        scene_manager.register_scene(
            "menu", []() { return std::make_unique<MenuScene>(); });

        change_scene("menu");
    }

    void on_shutdown() override {}
};

int main() {
    Game game;
    game.run();
    return 0;
}
