#include "engine/ui/node.hpp"
#include "fill.hpp"

using namespace varicle;
using namespace varicle::ui;

Vec2 varicle::ui::FillStrategy::measure(
    std::vector<std::shared_ptr<UINode>>& nodes,
    LayoutConstraint                      constraint
) {
    Vec2 preferred_size = Vec2::ZERO();

    for (auto& node : nodes) {
        node->measure_layout(constraint);
        Vec2 node_prefered_size = node->preferred_size;
        preferred_size.x = std::max(preferred_size.x, node_prefered_size.x);
        preferred_size.y = std::max(preferred_size.y, node_prefered_size.y);
    }

    return { preferred_size.x, preferred_size.y };
}

void FillStrategy::arrange(
    std::vector<std::shared_ptr<UINode>>& nodes,
    Rect                                  rect
) {
    Rect child_rect = rect;
    for (auto& node : nodes) {
        node->update_layout(child_rect);
    }
}
