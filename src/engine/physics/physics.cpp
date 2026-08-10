#include "physics.hpp"

using namespace varicle::physics;
using namespace varicle::shape;

void varicle::physics::PhysicsServer2D::debug_draw_colliders() {}

// Shape

ShapeID PhysicsServer2D::create_shape(ShapeData shape) {
    return m_shapes.emplace(shape);
}

const ShapeData *PhysicsServer2D::get_shape(const ShapeID shape_id) const {
    return m_shapes.get(shape_id);
}

void PhysicsServer2D::destroy_shape(ShapeID shape_id) {
    m_shapes.remove(shape_id);
}

// Collider
ColliderID PhysicsServer2D::create_collider(BodyID body_id, ShapeID shape_id,
                                            Vec2 offset) {
    return m_colliders.emplace({body_id, shape_id, offset});
}
const ColliderData *
PhysicsServer2D::get_collider(ColliderID collider_id) const {

    return m_colliders.get(collider_id);
}
void PhysicsServer2D::destroy_collider(ColliderID collider_id) {
    m_colliders.remove(collider_id);
}

// Body
BodyID PhysicsServer2D::create_body(BodyMode mode, Vec2 position) {
    BodyData body;
    body.mode = mode;
    body.position = position;
    return m_bodies.emplace(body);
}


BodyData *PhysicsServer2D::get_body(BodyID body_id) {
    return m_bodies.get(body_id);
}
const BodyData *PhysicsServer2D::get_body(BodyID body_id) const {
    return m_bodies.get(body_id);
}

void PhysicsServer2D::destroy_body(BodyID body_id) { m_bodies.remove(body_id); }

// Processing

void PhysicsServer2D::step(float dt) {
    integrate_positions(dt);
}

void PhysicsServer2D::integrate_positions(float dt) {
    auto& bodies = m_bodies.get_data();

    for (auto &body : bodies) {
        switch (body.mode) {
        case BodyMode::KINEMATIC:
            body.position = body.position + (body.velocity * dt);
            break;
        case BodyMode::STATIC:
            break;
        case BodyMode::ANIMATED:
            break;
        case BodyMode::DYNAMIC:
            break;
        }
    }
}
