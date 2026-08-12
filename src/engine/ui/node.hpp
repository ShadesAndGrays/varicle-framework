#pragma once
#include "engine/core/engine-variant/engine-variant.hpp"
#include "engine/ui/anchor.hpp"
#include "engine/ui/rect.hpp"
#include <memory>
#include <string>

namespace varicle::ui {

class UINode : public std::enable_shared_from_this<UINode> {
  public:
    std::string name;
    bool        visible = true;
    bool        active  = true;

    // Layout
    UIAnchor anchor = anchors::TopLeft;
    Vec2     pivot  = { 0.0f, 0.0f };

    float offset_left   = 0.0f;
    float offset_top    = 0.0f;
    float offset_right  = 100.0f; // Width if min_x == max_x
    float offset_bottom = 100.0f; // Height if min_y == max_y

  protected:
    Rect m_global_rect = { 0, 0, 0, 0 };

    std::weak_ptr<UINode>                m_parent;
    std::vector<std::shared_ptr<UINode>> m_children;

  public:
    virtual ~UINode() = default; //

    void add_child(std::shared_ptr<UINode> child) {
        child->m_parent = shared_from_this();
        m_children.push_back(child);
    }

    Rect get_global_rect() const { return m_global_rect; }

    virtual void update_layout(Rect parent_rect) {

        float anchor_left = parent_rect.x + (parent_rect.width * anchor.min_x);
        float anchor_top  = parent_rect.y + (parent_rect.height * anchor.min_y);
        float anchor_right = parent_rect.x + (parent_rect.width * anchor.max_x);
        float anchor_bottom =
            parent_rect.y + (parent_rect.height * anchor.max_y);

        // Determine final screen bounds
        if (anchor.min_x == anchor.max_x) {
            // Point anchor: width comes from offset_right, position adjusted by
            // pivot
            m_global_rect.width = offset_right;
            m_global_rect.x =
                anchor_left + offset_left - (m_global_rect.width * pivot.x);
        } else {
            // Stretch anchor: edges are pinned to parent anchors
            m_global_rect.x = anchor_left + offset_left;
            m_global_rect.width =
                (anchor_right - offset_right) - m_global_rect.x;
        }

        if (anchor.min_y == anchor.max_y) {
            m_global_rect.height = offset_bottom;
            m_global_rect.y =
                anchor_top + offset_top - (m_global_rect.height * pivot.y);
        } else {
            m_global_rect.y = anchor_top + offset_top;
            m_global_rect.height =
                (anchor_bottom - offset_bottom) - m_global_rect.y;
        }

        // Recursively update children using this node's new global rect
        for (auto& child : m_children) {
            if (child->visible) {
                child->update_layout(m_global_rect);
            }
        }
    }

    // 2. INPUT PASS: Children to parent
    virtual bool process_input(Vec2 mouse_pos) {
        if (!visible || !active)
            return false;

        // Process children in reverse order (topmost rendered elements get
        // input first)
        for (auto it = m_children.rbegin(); it != m_children.rend(); ++it) {
            if ((*it)->process_input(mouse_pos)) {
                return true; // Input was consumed by a child!
            }
        }
        return false;
    }

    // 3. RENDER PASS: Draw back-to-front
    virtual void draw() {
        if (!visible)
            return;

        draw_self();

        for (auto& child : m_children) {
            child->draw();
        }
    }

  protected:
    virtual void draw_self() {}
};


class UIUtil {
    

};

} // namespace varicle::ui
