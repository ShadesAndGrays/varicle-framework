#include "varicle.hpp"
using namespace entt::literals;

namespace v = varicle;

struct ZoneEntered {
    int zone_id;
};

class MainScene : public v::Scene {
  private:
    entt::registry registry;
    entt::entity   player;
    float          player_speed = 100.0f;
    bool           pause        = true;

  public:
    void init() override;

    void update(float dt) override;

    void render() override;

    void ui() override {}

    void deinit() override {}

    void add_ground();
    void add_player();
    void add_zone(v::Vec2 intial_pos, bool connect_signals, std::string name);
    static void _on_zone_entered(ZoneEntered);
};

class Game : public v::Application {

  public:
    void on_init() override {
        auto& sm = v::ServiceLocator::get<v::SceneManager>();
        sm.register_scene("main", []() {
            return std::make_unique<MainScene>();
        });

        sm.switch_to_scene("main");
    }

    void on_shutdown() override {}
};

void MainScene::init() {
    auto& physics_server_2d =
        v::ServiceLocator::get<v::physics::PhysicsServer2D>();
    physics_server_2d.debug = true;
    add_ground();
    add_player();
    add_zone(v::Vec2{ 150, 300 }, true, "ZONE_1");
    add_zone(v::Vec2{ 450, 300 }, true, "ZONE_2");
}

void MainScene::add_player() {
    player = registry.create();

    const float width  = 10.0f;
    const float height = 10.0f;

    v::SpriteUtil::add_sprite_component(
        registry,
        player,
        {
            .texture_path = "",
            .width        = width,
            .height       = height,
        }
    );

    v::PhysicsUtil::add_kinematic_body_component(registry, player);
    v::PhysicsUtil::add_rect_collider(
        registry, player, { width / 2, height / 2 }
    );
    v::PhysicsUtil::set_rotation(registry, player, v::constants::pi / 3.9f);
    v::PhysicsUtil::set_position(registry, player, v::Vec2{ 300, 300 });
    v::PhysicsUtil::set_velocity(registry, player, { -player_speed, 0.0f });
}

void MainScene::add_ground() {
    const float width  = 1000.0f;
    const float height = 30.0f;

    const auto ground = registry.create();
    v::SpriteUtil::add_sprite_component(
        registry, ground, { .width = width, .height = height }
    );
    v::SpriteUtil::add_tint_component(registry, ground, { v::Color::Black() });
    v::PhysicsUtil::add_static_body_component(registry, ground);
    v::PhysicsUtil::set_position(registry, ground, v::Vec2{ 300, 700 });
    v::PhysicsUtil::add_rect_collider(
        registry, ground, { width / 2.0f, height / 2.0f }
    );
}

void MainScene::add_zone(
    v::Vec2     intial_pos,
    bool        connect_signals,
    std::string name
) {
    const auto zone = registry.create();
    v::PhysicsUtil::add_zone_body_component(registry, zone);
    v::PhysicsUtil::set_position(registry, zone, intial_pos);
    v::PhysicsUtil::add_circle_collider(registry, zone, 100);

    if (!connect_signals)
        return;
    v::ServiceLocator::get<v::event::EventBus>()
        .subscribe<v::physics::EventBodyEntered>(
            [this, zone, name](v::physics::EventBodyEntered event) {
                if (v::PhysicsUtil::is_entity_body(
                        registry, zone, event.native_zone_body_id
                    )) {
                    std::cout << name << " Entered" << std::endl;
                }
            }
        );

    v::ServiceLocator::get<v::event::EventBus>()
        .subscribe<v::physics::EventBodyExited>(
            [this, zone, name](v::physics::EventBodyExited event) {
                if (v::PhysicsUtil::is_entity_body(
                        registry, zone, event.native_zone_body_id
                    )) {
                    std::cout << name << "Exited" << std::endl;
                }
            }
        );
}

void MainScene::update(float dt) {

    if (IsKeyDown(KEY_LEFT)) {
        v::PhysicsUtil::set_velocity(registry, player, { -player_speed, 0.0f
        });
    } else if (IsKeyDown(KEY_RIGHT)) {
        v::PhysicsUtil::set_velocity(registry, player, { player_speed, 0.0f
        });
    } else if (IsKeyDown(KEY_UP)) {
        v::PhysicsUtil::set_velocity(registry, player, { 0.0f, -player_speed
        });
    } else if (IsKeyDown(KEY_DOWN)) {
        v::PhysicsUtil::set_velocity(registry, player, { 0.0f, player_speed
        });
    } else {
        v::PhysicsUtil::set_velocity(registry, player, { 0.0f, 0.0f });
    }
    v::PhysicsSystem::update_physics_system(registry, dt);
    v::TransformSystem::update_global_transform(registry);
}

void MainScene::render() {
    v::RenderSystem::update_render_system(registry);
}

int main() {
    Game game;
    game.run();
    return 0;
}
