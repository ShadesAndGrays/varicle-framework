#pragma once

#include "varicle.hpp"

namespace v = varicle;

class LayoutTestScene : public v::Scene {
  private:
    varicle::ui::UIFactory         ui_factory;
    std::shared_ptr<v::ui::UINode> root;

  public:
    void init() override;

    void update(float dt) override;

    void render() override;

    void ui() override;

    void deinit() override {}
};
