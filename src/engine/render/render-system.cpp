#include "engine/render/render-system.hpp"
#include "engine/asset/raylib-asset.hpp"
#include "engine/core/service-locator.hpp"
#include "engine/ecs/components.hpp"

#include <entt/entt.hpp>
#include <raylib.h>

namespace varicle {

void update_render_system(entt::registry &registry) {
    auto view = registry.view<const Sprite, const GlobalTransform2D>();

    for (entt::entity entity : view) {
        const Sprite &sprite = view.get<Sprite>(entity);
        auto [global_position, global_scale, global_rotation] =
            view.get<GlobalTransform2D>(entity);
        auto texture =
            sprite.texture_path == ""
                ? nullptr
                : ServiceLocator::get<RaylibAssetLoader>().get_texture(
                      sprite.texture_path);

        float width = sprite.width * global_scale;
        float height = sprite.height * global_scale;
        float rotation = sprite.rotation + global_rotation;

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
                Vector2{width * 0.5f, height * 0.5f}, rotation, WHITE);

        } else {
            DrawRectanglePro(
                Rectangle{sprite.offset_x + global_position.x,
                          sprite.offset_y + global_position.y, width, height},
                Vector2{width * 0.5f, height * 0.5f}, rotation, PURPLE);
        }
    }
}
} // namespace varicle
