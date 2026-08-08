#pragma once

#include "engine/core/color.hpp"
#include "transform.hpp"
#include <entt/entt.hpp>
#include <string>

namespace varicle::components {

struct Sprite {
    std::string texture_path = "";
    float offset_x = 0;
    float offset_y = 0;
    float width = 64;
    float height = 64;
    bool flip_h = false;
    bool flip_v = false;
    float rotation = 0;
};

struct Tint {
    varicle::Color tint = varicle::Color::White();
};

} // namespace varicle::components

namespace varicle {

class SpriteUtil {
  public:
    static void
    add_sprite_component(entt::registry &registry, entt::entity entity,
                         const varicle::components::Sprite &sprite) {
        registry.emplace_or_replace<varicle::components::Sprite>(entity) =
            sprite;

        registry.emplace_or_replace<varicle::components::GlobalTransform2D>(
            entity) ;

        registry.emplace_or_replace<varicle::components::LocalTransform2D>(
            entity) ;
    }

    static void add_tint_component(entt::registry &registry,
                                   entt::entity entity,
                                   const varicle::components::Tint &tint) {
        registry.emplace_or_replace<varicle::components::Tint>(entity) = tint;
    }
};

} // namespace varicle
