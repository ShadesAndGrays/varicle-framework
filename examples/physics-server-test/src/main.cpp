#include "engine/core/application.hpp"
#include "engine/core/engine-variant/engine-variant.hpp"
#include "engine/ecs/physics.hpp"
#include "engine/ecs/sprite.hpp"
#include "engine/ecs/transform.hpp"
#include "engine/ecs/tween.hpp"
#include "engine/physics/physics.hpp"
#include "engine/render/render-system.hpp"
#include "engine/scene/scene.hpp"

#include <entt/entt.hpp>
#include <raylib.h>

namespace v = varicle;

class MainScene : public v::Scene {
  private:
    entt::registry registry;
    entt::entity player;

  public:
    void init() override;

    void update(float dt) override;

    void render() override;

    void ui() override {}

    void deinit() override {}
};

class Game : public v::Application {

  public:
    void on_init() override {
        auto &sm = v::ServiceLocator::get<v::SceneManager>();
        sm.register_scene("main",
                          []() { return std::make_unique<MainScene>(); });

        sm.switch_to_scene("main");
    }

    void on_shutdown() override {}
};

void MainScene::init() {
    player = registry.create();
    v::SpriteUtil::add_sprite_component(registry, player,
                                        {
                                            .texture_path = "",
                                            .width = 100,
                                            .height = 100,
                                        });

    v::PhysicsUtil::add_kinematic_body_component(registry, player);
    v::PhysicsUtil::set_position(registry, player, v::Vec2{300, 300});
    v::PhysicsUtil::set_velocity(registry,player,{0,100});

}

void MainScene::update(float dt) {
    v::RenderSystem::update_render_system(registry);
    v::TransformSystem::update_global_transform(registry);
    v::PhysicsSystem::update_physics_system(registry, dt);
}

void MainScene::render() {}

int main() {
    Game game;
    game.run();
    return 0;
}
