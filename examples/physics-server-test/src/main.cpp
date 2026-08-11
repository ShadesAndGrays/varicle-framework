#include "varicle.hpp"

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

    void add_ground();
    void add_player();
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
    auto &physics_server_2d =
        v::ServiceLocator::get<v::physics::PhysicsServer2D>();
    physics_server_2d.debug = true;
    add_player();
    add_ground();
}

void MainScene::add_player() {
    player = registry.create();
    v::SpriteUtil::add_sprite_component(registry, player,
                                        {
                                            .texture_path = "",
                                            .width = 100,
                                            .height = 100,
                                        });

    v::PhysicsUtil::add_dynamic_body_component(registry, player);
    v::PhysicsUtil::add_rect_collider(registry, player, {50, 50});
    v::PhysicsUtil::set_rotation(registry, player, v::constants::pi / 3.9f);
    v::PhysicsUtil::set_position(registry, player, v::Vec2{400, 100});
}

void MainScene::add_ground() {
    const float width = 1000.0f;
    const float height = 30.0f;

    const auto ground = registry.create();
    v::SpriteUtil::add_sprite_component(registry, ground,
                                        {.width = width, .height = height});
    v::SpriteUtil::add_tint_component(registry, ground, {v::Color::Black()});
    v::PhysicsUtil::add_static_body_component(registry, ground);
    v::PhysicsUtil::set_position(registry, ground, v::Vec2{300, 700});
    v::PhysicsUtil::add_rect_collider(registry, ground,
                                      {width / 2.0f, height / 2.0f});
}

void MainScene::update(float dt) {
    v::PhysicsSystem::update_physics_system(registry, dt);
    v::TransformSystem::update_global_transform(registry);

    if (IsKeyPressed(KEY_SPACE)) {
        v::PhysicsUtil::set_position(registry, player, v::Vec2{400, 100});
    }
}

void MainScene::render() { v::RenderSystem::update_render_system(registry); }

int main() {
    Game game;
    game.run();
    return 0;
}
