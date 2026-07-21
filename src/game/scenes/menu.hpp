#pragma once

#include "engine/scene/scene.hpp"

namespace v = varicle;

class MenuScene : public v::Scene {
  public:
    void init() override;
    void update(float dt) override;
    void render() override;
    void ui() override;
};
