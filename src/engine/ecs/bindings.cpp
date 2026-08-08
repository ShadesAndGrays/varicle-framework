#include "bindings.hpp"
#include "components.hpp"
#include "engine/core/engine-variant/engine-variant-property-id.hpp"

using namespace entt::literals;
using namespace varicle::components;

void varicle::register_all_component_properties(PropertyDatabase &db) {

    //----------------------------------------------------------
    // LocalTransform2D
    //----------------------------------------------------------
    db.register_property(
        PropertyID::TransformPosition,
        PropertyRegistry::bind_field(PropertyID::TransformPosition,
                                     &LocalTransform2D::position));

    db.register_property(
        PropertyID::TransformScale,
        PropertyRegistry::bind_field(PropertyID::TransformScale,
                                     &LocalTransform2D::scale));

    db.register_property(
        PropertyID::TransformRotation,
        PropertyRegistry::bind_field(PropertyID::TransformRotation,
                                     &LocalTransform2D::rotation));

    //----------------------------------------------------------
    // GlobalTransform2D
    //----------------------------------------------------------
    db.register_property(
        PropertyID::GlobalTransformPosition,
        PropertyRegistry::bind_field(PropertyID::GlobalTransformPosition,
                                     &GlobalTransform2D::position));

    db.register_property(
        PropertyID::GlobalTransformScale,
        PropertyRegistry::bind_field(PropertyID::GlobalTransformScale,
                                     &GlobalTransform2D::scale));

    db.register_property(
        PropertyID::GlobalTransformRotation,
        PropertyRegistry::bind_field(PropertyID::GlobalTransformRotation,
                                     &GlobalTransform2D::rotation));

    //----------------------------------------------------------
    // Velocity
    //----------------------------------------------------------

    db.register_property(PropertyID::VelocityX,
                         PropertyRegistry::bind_field(PropertyID::VelocityX,
                                                      &Velocity::dx));

    db.register_property(PropertyID::VelocityY,
                         PropertyRegistry::bind_field(PropertyID::VelocityY,
                                                      &Velocity::dy));

    //----------------------------------------------------------
    // Sprite
    //----------------------------------------------------------

    db.register_property(
        PropertyID::SpriteTexture,
        PropertyRegistry::bind_field(PropertyID::SpriteTexture,
                                     &Sprite::texture_path));

    db.register_property(
        PropertyID::SpriteOffsetY,
        PropertyRegistry::bind_field(PropertyID::SpriteOffsetY,
                                     &Sprite::offset_y));

    db.register_property(
        PropertyID::SpriteOffsetX,
        PropertyRegistry::bind_field(PropertyID::SpriteOffsetX,
                                     &Sprite::offset_x));

    db.register_property(PropertyID::SpriteWidth,
                         PropertyRegistry::bind_field(PropertyID::SpriteWidth,
                                                      &Sprite::width));

    db.register_property(
        PropertyID::SpriteHeight,
        PropertyRegistry::bind_field(PropertyID::SpriteHeight,
                                     &Sprite::height));

    db.register_property(
        PropertyID::SpriteFlipH,
        PropertyRegistry::bind_field(PropertyID::SpriteFlipH,
                                     &Sprite::flip_h));

    db.register_property(
        PropertyID::SpriteFlipV,
        PropertyRegistry::bind_field(PropertyID::SpriteFlipV,
                                     &Sprite::flip_v));

    db.register_property(
        PropertyID::SpriteRotation,
        PropertyRegistry::bind_field(PropertyID::SpriteRotation,
                                     &Sprite::rotation));
}
