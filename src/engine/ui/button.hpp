#pragma once
#include "engine/ui/node.hpp"
#include <functional>

namespace varicle::ui {

class UIButton : public UINode {
  public:
    std::string           text;
    std::function<void()> on_click;
    varicle::Color        bg_color = { 40, 40, 40, 200 };

  private:
    bool m_hovered = false;
    bool m_pressed = false;

  public:
    UIButton(std::string label) : text(std::move(label)) {}

    bool process_input(Vec2 mouse_pos) override {
        if (UINode::process_input(mouse_pos))
            return true;

        m_hovered = CheckCollisionPointRec(
            { mouse_pos.x, mouse_pos.y },
            { m_global_rect.x,
              m_global_rect.y,
              m_global_rect.width,
              m_global_rect.height }
        );

        if (m_hovered) {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                m_pressed = true;
            }
            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && m_pressed) {
                m_pressed = false;
                if (on_click)
                    on_click(); // Fire event!
            }
            return true; // Consume input focus so clicks don't hit physics
                         // world below
        }

        m_pressed = false;
        return false;
    }

  protected:
    void draw_self() override {
        ::Color col = m_hovered ? (m_pressed ? ::Color{ 120, 120, 120, 255 }
                                             : ::Color{ 90, 90, 90, 255 })
                                : ::Color{ 60, 60, 60, 255 };

        auto rec = Rectangle{ m_global_rect.x,
                              m_global_rect.y,
                              m_global_rect.width,
                              m_global_rect.height };
        DrawRectangleRec(rec, col);
        DrawRectangleLinesEx(rec, 1.0f, ::BLACK);

        // Draw centered text
        int font_size  = 18;
        int text_width = MeasureText(text.c_str(), font_size);
        DrawText(
            text.c_str(),
            static_cast<int>(
                m_global_rect.x + (m_global_rect.width - text_width) / 2.0f
            ),
            static_cast<int>(
                m_global_rect.y + (m_global_rect.height - font_size) / 2.0f
            ),
            font_size,
            ::BLACK
        );
    }
};

} // namespace varicle::ui
