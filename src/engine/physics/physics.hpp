#pragma once

#include "engine/core/engine-variant/engine-variant.hpp"
#include "engine/util/slot-map.hpp"

namespace varicle::physics {
using BodyID = structures::SlotID;
using ShapeID = structures::SlotID;
using ColliderID = structures::SlotID;

enum class BodyMode { STATIC, KINEMATIC, DYNAMIC, ANIMATED };

} // namespace varicle::physics

namespace varicle::shape {
struct CircleShape {
    float radius;
};
struct RectangleShape {
    Vec2 half_extents;
};

using ShapeData = std::variant<std::monostate, CircleShape, RectangleShape>;

} // namespace varicle::shape

namespace varicle::physics {

struct BodyData {
    Vec2 position = {0.0f, 0.0f};
    Vec2 velocity = {0.0f, 0.0f};

    BodyMode mode = BodyMode::STATIC;

    float inv_mass() const {
        return (mode == BodyMode::DYNAMIC) ? (1.0f / mass) : 0.0f;
    }

  private:
    float mass = 1.0f;
};

struct ColliderData {
    BodyID body_id;
    ShapeID shape_id;
    Vec2 offset = {0.0f, 0.0f};
};

class PhysicsServer2D {
  private:
    structures::SlotMap<BodyData> m_bodies;
    structures::SlotMap<ColliderData> m_colliders;
    structures::SlotMap<shape::ShapeData> m_shapes;

  public:
    PhysicsServer2D() = default;
    void debug_draw_colliders();

    // Shape
    ShapeID create_shape(shape::ShapeData shape);
    const shape::ShapeData *get_shape(ShapeID shape_id) const;
    void destroy_shape(ShapeID shape_id);

    // Collider
    ColliderID create_collider(BodyID body_id, ShapeID shape_id, Vec2 offset);
    const ColliderData *get_collider(ColliderID collider_id) const;
    void destroy_collider(ColliderID collider_id);

    // Body
    BodyID create_body(BodyMode mode, Vec2 position);
    const BodyData *get_body(BodyID body_id) const;
    BodyData *get_body(BodyID body_id);
    void destroy_body(BodyID body_id);

    // Result
    struct MovementResult {
        bool collided{false};
        Vec2 motion_applied{0.0f, 0.0f};
        Vec2 normal{0.0f, 0.0f};
        BodyID hit_body;
    };

    // The move_and_slide logic lives cleanly inside the server!
    MovementResult body_move_and_slide(BodyID body, const Vec2 &linear_velocity,
                                       float dt);

    void step(float dt);
    void integrate_positions(float dt);
};

// struct CollisionDetector {
//     // Circle vs Circle
//     bool operator()(const shape::CircleShape &a,
//                     const shape::CircleShape &b) const {}
//
//     // Circle vs Box
//     bool operator()(const shape::CircleShape &a,
//                     const shape::RectangleShape &b) const {}
//
//     // Box vs Circle (redirect)
//     bool operator()(const shape::RectangleShape &a,
//                     const shape::CircleShape &b) const {
//         return (*this)(b, a);
//     }
//
//     // Box vs Box
//     bool operator()(const shape::RectangleShape &a,
//                     const shape::RectangleShape &b) const {}
// };
} // namespace varicle::physics
