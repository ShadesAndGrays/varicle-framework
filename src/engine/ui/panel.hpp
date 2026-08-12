#pragma once
#include "engine/ui/node.hpp"

namespace varicle::ui {

class UIPanel : public UINode {
  public:
    varicle::Color bg_color = { 40, 40, 40, 200 };

  protected:
    void draw_self() override {
        DrawRectangleRec(
            Rectangle{
                m_global_rect.x,
                m_global_rect.y,
                m_global_rect.width,
                m_global_rect.height,
            },
            ColorUtil::to_raylib_color(bg_color)
        );
    }
};

} // namespace varicle::ui
