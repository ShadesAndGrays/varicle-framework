#include "bindings.hpp"
#include "components.hpp"
#include "engine/core/engine-variant/engine-variant-property-id.hpp"

using namespace entt::literals;

void varicle::register_all_component_properties(PropertyDatabase &db) {

    //----------------------------------------------------------
    // LocalTransform2D
    //----------------------------------------------------------
    db.register_property(
        PropertyID::TransformPosition,
        PropertyRegistry::bind_field(PropertyID::TransformPosition,
                                     &varicle::LocalTransform2D::position));

    db.register_property(
        PropertyID::TransformScale,
        PropertyRegistry::bind_field(PropertyID::TransformScale,
                                     &varicle::LocalTransform2D::scale));

    db.register_property(
        PropertyID::TransformRotation,
        PropertyRegistry::bind_field(PropertyID::TransformRotation,
                                     &varicle::LocalTransform2D::rotation));

    //----------------------------------------------------------
    // GlobalTransform2D
    //----------------------------------------------------------
    db.register_property(
        PropertyID::GlobalTransformPosition,
        PropertyRegistry::bind_field(PropertyID::GlobalTransformPosition,
                                     &varicle::GlobalTransform2D::position));

    db.register_property(
        PropertyID::GlobalTransformScale,
        PropertyRegistry::bind_field(PropertyID::GlobalTransformScale,
                                     &varicle::GlobalTransform2D::scale));

    db.register_property(
        PropertyID::GlobalTransformRotation,
        PropertyRegistry::bind_field(PropertyID::GlobalTransformRotation,
                                     &varicle::GlobalTransform2D::rotation));

    //----------------------------------------------------------
    // Velocity
    //----------------------------------------------------------

    db.register_property(PropertyID::VelocityX,
                         PropertyRegistry::bind_field(PropertyID::VelocityX,
                                                      &varicle::Velocity::dx));

    db.register_property(PropertyID::VelocityY,
                         PropertyRegistry::bind_field(PropertyID::VelocityY,
                                                      &varicle::Velocity::dy));

    //----------------------------------------------------------
    // Sprite
    //----------------------------------------------------------

    db.register_property(
        PropertyID::SpriteTexture,
        PropertyRegistry::bind_field(PropertyID::SpriteTexture,
                                     &varicle::Sprite::texture_path));

    db.register_property(
        PropertyID::SpriteOffsetY,
        PropertyRegistry::bind_field(PropertyID::SpriteOffsetY,
                                     &varicle::Sprite::offset_y));

    db.register_property(
        PropertyID::SpriteOffsetX,
        PropertyRegistry::bind_field(PropertyID::SpriteOffsetX,
                                     &varicle::Sprite::offset_x));

    db.register_property(PropertyID::SpriteWidth,
                         PropertyRegistry::bind_field(PropertyID::SpriteWidth,
                                                      &varicle::Sprite::width));

    db.register_property(
        PropertyID::SpriteHeight,
        PropertyRegistry::bind_field(PropertyID::SpriteHeight,
                                     &varicle::Sprite::height));

    db.register_property(
        PropertyID::SpriteFlipH,
        PropertyRegistry::bind_field(PropertyID::SpriteFlipH,
                                     &varicle::Sprite::flip_h));

    db.register_property(
        PropertyID::SpriteFlipV,
        PropertyRegistry::bind_field(PropertyID::SpriteFlipV,
                                     &varicle::Sprite::flip_v));

    db.register_property(
        PropertyID::SpriteRotation,
        PropertyRegistry::bind_field(PropertyID::SpriteRotation,
                                     &varicle::Sprite::rotation));
}
