#pragma once
#include "engine/core/service-locator.hpp"
#include "engine/ecs/transform.hpp"
#include "engine/physics/physics.hpp"

namespace varicle::components {

struct Body2D {
    physics::BodyID body_id;
};

} // namespace varicle::components
namespace varicle {

class PhysicsSystem {
  public:
    static void update_physics_system(entt::registry &registry, float dt) {
        using namespace components;

        auto physic_group = registry.view<const Body2D, LocalTransform2D>();

        physic_group.each(
            [dt](const Body2D &body_component, LocalTransform2D &transform) {
                auto &physics_server_2d =
                    ServiceLocator::get<physics::PhysicsServer2D>();
                auto body = physics_server_2d.get_body(body_component.body_id);
                transform.position = body->position;
            });
    }
};

class PhysicsUtil {
  private:
    static void add_body_component(entt::registry &registry, entt::entity e,
                                   physics::BodyMode mode) {

        auto &physics_server_2d =
            ServiceLocator::get<physics::PhysicsServer2D>();
        Vec2 initial_position = {.0f, .0f};

        if (const auto transform =
                registry.try_get<components::GlobalTransform2D>(e)) {
            initial_position = transform->position;
        };
        auto &body_2d = registry.emplace<components::Body2D>(e);
        body_2d.body_id = physics_server_2d.create_body(mode, initial_position);
    }

  public:
    static void set_velocity(entt::registry &registry, entt::entity e,
                             Vec2 velocity) {
        if (const auto body_component =
                registry.try_get<components::Body2D>(e)) {
            auto &physics_server_2d =
                ServiceLocator::get<physics::PhysicsServer2D>();
            physics_server_2d.get_body(body_component->body_id)->velocity =
                velocity;
        }
    }
    static void set_position(entt::registry &registry, entt::entity e,
                             Vec2 position) {
        if (const auto body_component =
                registry.try_get<components::Body2D>(e)) {
            auto &physics_server_2d =
                ServiceLocator::get<physics::PhysicsServer2D>();
            physics_server_2d.get_body(body_component->body_id)->position =
                position;
        }
    }
    static void add_static_body_component(entt::registry &registry,
                                          entt::entity e) {
        add_body_component(registry, e, physics::BodyMode::STATIC);
    }

    static void add_kinematic_body_component(entt::registry &registry,
                                             entt::entity e) {
        add_body_component(registry, e, physics::BodyMode::KINEMATIC);
    }

    static void add_dynamic_body_component(entt::registry &registry,
                                           entt::entity e) {
        add_body_component(registry, e, physics::BodyMode::DYNAMIC);
    }

    static void add_collider_to_body(entt::registry &registry, entt::entity e,
                                     float radius) {
        auto &physics_server_2d =
            ServiceLocator::get<physics::PhysicsServer2D>();

        if (const auto body = registry.try_get<components::Body2D>(e)) {
            auto shape_id =
                physics_server_2d.create_shape(shape::CircleShape{radius});
            physics_server_2d.create_collider(body->body_id, shape_id, {0, 0});
        }
    }
};
} // namespace varicle
