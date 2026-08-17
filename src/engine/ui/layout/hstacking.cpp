#include "hstacking.hpp"
#include "engine/ui/node.hpp"
#include "fill.hpp"

using namespace varicle;
using namespace varicle::ui;

Vec2 HStackingStrategy::measure(
    std::vector<std::shared_ptr<UINode>>& nodes,
    LayoutConstraint                      constraint
) {
    return FillStrategy().measure(nodes, constraint);
}
void HStackingStrategy::arrange(
    std::vector<std::shared_ptr<UINode>>& nodes,
    Rect                                  rect
) {
    const int number_of_children = nodes.size();

    if (number_of_children == 0) {
        return;
    } else {

        Rect child_rect = {
            rect.x,
            rect.y,
            rect.width,
            rect.height,
        };

        // free space ratio total
        float slack_ratio = 0.0f;

        // acutal free space
        float slack_space = rect.width;

        for (auto& node : nodes) {
            if (node->sizing_mode == ui::SizingMode::FILL) {
                slack_ratio += node->bias;

            } else {
                slack_space -= node->preferred_size.x;
            }
        }

        for (auto i = 0; i < nodes.size(); i++) {

            float child_size;

            switch (nodes[i]->sizing_mode) {

            case EXACT:
                child_size = nodes[i]->preferred_size.x;
                break;

            case FILL:
                child_size = std::max(
                    (slack_space * (nodes[i]->bias / slack_ratio)),
                    nodes[i]->preferred_size.x
                );
                break;
            }

            child_rect.width = child_size;
            nodes[i]->update_layout(child_rect);
            child_rect.x += child_rect.width;
        }
    }

    // const auto width = parent_rect.width / static_cast<float>(nodes.size());
    // for (auto i = 0; i < nodes.size(); i++) {
    //     nodes[i]->x = parent_rect.x + (width * i);
    //     nodes[i]->y = parent_rect.y;
    // }
}
