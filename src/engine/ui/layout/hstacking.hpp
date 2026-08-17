#pragma once

#include "layout.hpp"

namespace varicle::ui {

class HStackingStrategy : public ILayoutStrategy {

  private:
    float m_gap = 0.0f;

  public:
    void  set_gap(float gap);
    float get_gap(float gap);

    Vec2 measure(
        std::vector<std::shared_ptr<UINode>>& nodes,
        LayoutConstraint                      constraint
    ) override;

    void
    arrange(std::vector<std::shared_ptr<UINode>>& nodes, Rect rect) override;
};

} // namespace varicle::ui
