#include "engine/core/application.hpp"
#include "engine/core/engine-variant/engine-variant.hpp"
#include "engine/ecs/sprite.hpp"
#include "engine/ecs/transform.hpp"
#include "engine/ecs/tween.hpp"
#include "engine/render/render-system.hpp"
#include "engine/scene/scene.hpp"

#include <entt/entt.hpp>
#include <format>
#include <raylib.h>

namespace v = varicle;

class MainScene : public v::Scene {
  private:
    entt::registry registry;
    v::TweenManager tm;
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
    v::TransformUtil::set_position(registry, player, v::Vec2{100, 100});
    v::SpriteUtil::add_tint_component(registry, player, {v::Color::Black()});
}
void MainScene::update(float dt) {
    if (IsKeyPressed(KEY_SPACE)) {
        tm.create_tween(player, v::PropertyID::TransformPosition,
                        v::Vec2{100, 100}, v::Vec2{100, 600}, 1)
            .set_curve([](float a){return v::Curve::smoothstep(a);})
            .set_ease(v::EaseMode::In);
        // [](float alpha) { return v::Ease::bounce_out(alpha, 8.0f, 6.0f); });
    }
    tm.update(registry, dt);
    v::TransformSystem::update_global_transform(registry);
    v::RenderSystem::update_render_system(registry);
}
void MainScene::render() {}

int main() {
    Game game;
    game.run();
    return 0;
}
