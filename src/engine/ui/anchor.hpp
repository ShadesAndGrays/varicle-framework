#pragma once
namespace varicle::ui {

struct UIAnchor {
    // 0.0 = Left/Top, 0.5 = Center, 1.0 = Right/Bottom
    float min_x = 0.0f, min_y = 0.0f; // Parent anchor start
    float max_x = 0.0f, max_y = 0.0f; // Parent anchor end
};

// Common Anchor Presets
namespace anchors {
inline const UIAnchor TopLeft{ 0.0f, 0.0f, 0.0f, 0.0f };
inline const UIAnchor TopRight{ 1.0f, 0.0f, 1.0f, 0.0f };
inline const UIAnchor BottomLeft{ 0.0f, 1.0f, 0.0f, 1.0f };
inline const UIAnchor BottomRight{ 1.0f, 1.0f, 1.0f, 1.0f };
inline const UIAnchor Center{ 0.5f, 0.5f, 0.5f, 0.5f };
inline const UIAnchor FullStretch{ 0.0f, 0.0f, 1.0f, 1.0f };
} // namespace anchors

} // namespace varicle::ui
