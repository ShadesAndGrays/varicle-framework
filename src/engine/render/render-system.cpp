#include "engine/render/render-system.hpp"
#include "engine/asset/raylib-asset.hpp"
#include "engine/core/service-locator.hpp"
#include "engine/ecs/components.hpp"

#include <entt/entt.hpp>
#include <raylib.h>

inline ::Color ToRaylibColor(const varicle::Color &c) {
    return ::Color{c.r, c.g, c.b, c.a};
}

void varicle::RenderSystem::update_render_system(entt::registry &registry) {
    auto view = registry.view<const components::Sprite,
                              const components::GlobalTransform2D>();

    for (entt::entity entity : view) {
        const components::Sprite &sprite = view.get<components::Sprite>(entity);

        auto [global_position, global_scale, global_rotation] =
            view.get<components::GlobalTransform2D>(entity);

        auto texture =
            sprite.texture_path == ""
                ? nullptr
                : ServiceLocator::get<RaylibAssetLoader>().get_texture(
                      sprite.texture_path);

        float width = sprite.width * global_scale;
        float height = sprite.height * global_scale;
        float rotation = sprite.rotation + (global_rotation / PI) * 180;

        ::Color raylibTint =
            texture ? ::WHITE
                    : ::PURPLE; // set default color based on texture presence
        if (components::Tint *tint_component =
                registry.try_get<components::Tint>(entity)) {
            raylibTint = ToRaylibColor(tint_component->tint);
        }

        if (texture) {
            DrawTexturePro(
                *(texture),
                Rectangle{
                    0.0f,
                    0.0f,
                    static_cast<float>(sprite.flip_h ? -texture->width
                                                     : texture->width),
                    static_cast<float>(sprite.flip_v ? -texture->height
                                                     : texture->height),
                },
                Rectangle{
                    sprite.offset_x + global_position.x,
                    sprite.offset_y + global_position.y,
                    width,
                    height,
                },
                Vector2{width * 0.5f, height * 0.5f}, rotation, raylibTint);

        } else {
            DrawRectanglePro(
                Rectangle{sprite.offset_x + global_position.x,
                          sprite.offset_y + global_position.y, width, height},
                Vector2{width * 0.5f, height * 0.5f}, rotation, raylibTint);
        }
    }
}
