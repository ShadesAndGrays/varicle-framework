#include "engine/render/render-system.hpp"
#include "engine/ecs/components.hpp"

#include<raylib.h>
#include <entt/entt.hpp>

namespace varicle {

    void update_render_system(entt::registry &registry){
        auto view = registry.view<const Sprite, const Position>();

        for (entt::entity entity : view){
            const Sprite &sprite = view.get<Sprite>(entity);
            const Position &pos = view.get<Position>(entity);

            if (sprite.texture){
                DrawTexturePro(
                        *(sprite.texture),
                        Rectangle{
                        0,
                        0,
                        (float)sprite.texture->width,
                        (float)sprite.texture->height,
                        },
                        Rectangle {
                        sprite.offset_x + pos.x,
                        sprite.offset_y + pos.y,
                        sprite.width,
                        sprite.height
                        },
                        Vector2 {sprite.width * 0.5f, sprite.height*0.5f},
                        sprite.rotation,
                        WHITE);

            }else{
                DrawRectanglePro(Rectangle {
                        sprite.offset_x + pos.x,
                        sprite.offset_y + pos.y,
                        sprite.width,
                        sprite.height
                        }, 
                        Vector2 {sprite.width * 0.5f, sprite.height*0.5f},
                        sprite.rotation,
                        PURPLE
                        );
            }
        }

    }
}
