#include "bindings.hpp"
#include "components.hpp"

using namespace entt::literals;

void varicle::register_all_component_properties(PropertyDatabase &db) {

    //----------------------------------------------------------
    // LocalTransform2D
    //----------------------------------------------------------
    db.register_property(
        "position"_hs,
        PropertyRegistry::bind_field("position"_hs,
                                     &varicle::LocalTransform2D::position));

    db.register_property("scale"_hs,
                         PropertyRegistry::bind_field(
                             "scale"_hs, &varicle::LocalTransform2D::scale));

    db.register_property(
        "rotation"_hs,
        PropertyRegistry::bind_field("rotation"_hs,
                                     &varicle::LocalTransform2D::rotation));

    //----------------------------------------------------------
    // GlobalTransform2D
    //----------------------------------------------------------
    db.register_property(
        "global_position"_hs,
        PropertyRegistry::bind_field("global_position"_hs,
                                     &varicle::GlobalTransform2D::position));

    db.register_property("global_scale"_hs,
                         PropertyRegistry::bind_field(
                             "global_scale"_hs, &varicle::GlobalTransform2D::scale));

    db.register_property(
        "global_rotation"_hs,
        PropertyRegistry::bind_field("global_rotation"_hs,
                                     &varicle::GlobalTransform2D::rotation));

    //----------------------------------------------------------
    // Velocity
    //----------------------------------------------------------

    db.register_property(
        "velocity:x"_hs,
        PropertyRegistry::bind_field("velocity:x"_hs, &varicle::Velocity::dx));

    db.register_property(
        "velocity:y"_hs,
        PropertyRegistry::bind_field("velocity:y"_hs, &varicle::Velocity::dy));

    //----------------------------------------------------------
    // Sprite
    //----------------------------------------------------------

    db.register_property(
        "sprite:texture_path"_hs,
        PropertyRegistry::bind_field("sprite:texture_path"_hs, &varicle::Sprite::texture_path));

    db.register_property(
        "sprite:offset:y"_hs,
        PropertyRegistry::bind_field("sprite:offset:y"_hs, &varicle::Sprite::offset_y));

    db.register_property(
        "sprite:offset:x"_hs,
        PropertyRegistry::bind_field("sprite:offset:x"_hs, &varicle::Sprite::offset_x));


    db.register_property(
        "sprite:width"_hs,
        PropertyRegistry::bind_field("sprite:width"_hs, &varicle::Sprite::width));


    db.register_property(
        "sprite:height"_hs,
        PropertyRegistry::bind_field("sprite:height"_hs, &varicle::Sprite::height));
    
    db.register_property(
        "sprite:flip_h"_hs,
        PropertyRegistry::bind_field("sprite:flip_h"_hs, &varicle::Sprite::flip_h));

    db.register_property(
        "sprite:flip_v"_hs,
        PropertyRegistry::bind_field("sprite:flip_v"_hs, &varicle::Sprite::flip_v));

    db.register_property(
        "sprite:rotation"_hs,
        PropertyRegistry::bind_field("sprite:rotation"_hs, &varicle::Sprite::rotation));

}
