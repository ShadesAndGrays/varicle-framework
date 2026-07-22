#pragma once

#include "engine/core/engine-variant/engine-variant.hpp"
#include <entt/entt.hpp>
#include <raylib.h>

namespace varicle {

struct Position {
    float x;
    float y;
};

struct Velocity {
    float dx;
    float dy;
};

struct LocalTransform2D {
    Vec2 position;
    float scale;
    float rotation;
};

struct GlobalTransform2D {
    Vec2 position;
    float scale;
    float rotation;
};

struct Sprite {
    std::string texture_path;
    float offset_x;
    float offset_y;
    float width;
    float height;
    bool flip_h;
    bool flip_v;
    float rotation;
};


} // namespace varicle
