#pragma once

#include "engine/scene/scene.hpp"
#include <entt/entt.hpp>

namespace v = varicle;

class MenuScene : public v::Scene {
  public:
    entt::registry registry;
    void init() override;
    void update(float dt) override;
    void render() override;
    void ui() override;
    void deinit() override;
};
