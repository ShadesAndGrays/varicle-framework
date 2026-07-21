#pragma once

#include <raylib.h>

namespace varicle{

    struct Position{
        float x;
        float y;
    };

    struct Velocity{
        float dx;
        float dy;
    };

    struct Sprite{
        Texture *texture;
        float offset_x;
        float offset_y;
        float width;
        float height;
        bool flip_h; 
        bool flip_v; 
        float rotation;
    };

}
