#pragma once

#include <entt/entt.hpp>

namespace varicle {
namespace PropertyID {
using namespace entt::literals;

// Guaranteed unique & typo-proof at compile time!
constexpr auto TransformPosition = "transform:position"_hs;
constexpr auto TransformScale = "transform:scale"_hs;
constexpr auto TransformRotation = "transform:rotation"_hs;

constexpr auto GlobalTransformPosition = "global_transform:position"_hs;
constexpr auto GlobalTransformScale = "global_transform:scale"_hs;
constexpr auto GlobalTransformRotation = "global_transform:rotation"_hs;

constexpr auto VelocityX = "velocity:x"_hs;
constexpr auto VelocityY = "velocity:y"_hs;

constexpr auto SpriteRotation = "sprite:rotation"_hs;
constexpr auto SpriteTexture = "sprite:texture"_hs;
constexpr auto SpriteOffsetX = "sprite:offset:x"_hs;
constexpr auto SpriteOffsetY = "sprite:offset:y"_hs;
constexpr auto SpriteWidth = "sprite:width"_hs;
constexpr auto SpriteHeight = "sprite:height"_hs;
constexpr auto SpriteFlipV = "sprite:flip_v"_hs;
constexpr auto SpriteFlipH = "sprite:flip_h"_hs;

} // namespace PropertyID

} // namespace varicle
