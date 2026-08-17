#pragma once

#ifdef OLD
#include "varicle.hpp"

namespace v = varicle;

class TestUIScene : public v::Scene {
  private:
    varicle::ui::UIFactory         ui_factory;
    std::shared_ptr<v::ui::UINode> ui_root;
    std::shared_ptr<v::ui::UINode> item;

  public:
    void init() override;

    void update(float dt) override;

    void render() override;

    void ui() override;

    void deinit() override {}
};
#endif
