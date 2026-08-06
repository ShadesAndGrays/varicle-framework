#pragma once

#include "engine/ecs/components.hpp"
#include <entt/entt.hpp>
namespace varicle {

class Hierachy {
  public:
    static void set_parent(entt::registry &registry, entt::entity child,
                           entt::entity parent) {
        remove_parent(registry, child);

        if (parent == entt::null)
            return;

        registry.emplace_or_replace<Parent>(child, parent);

        auto &children_component = registry.get_or_emplace<Children>(parent);
        children_component.children.push_back(child);
    }

    static void remove_parent(entt::registry &registry, entt::entity child) {
        Parent *parent_component = registry.try_get<Parent>(child);

        if (!parent_component ||
            parent_component->parent == entt::null) // if no parent return
            return;

        entt::entity previous_parent = parent_component->parent;

        if (auto *children_component =
                registry.try_get<Children>(previous_parent)) {
            auto &children = children_component->children;
            std::erase(children, child);

            if (children.empty()) { // if no more children
                registry.remove<Children>(previous_parent);
            }
        }

        registry.remove<Parent>(child);
    }

    static void destroy_entity(entt::registry &registry, entt::entity entity) {
        if (auto *children_component = registry.try_get<Children>(entity)) {
            auto children_copy = children_component->children;
            for (auto child : children_copy) {
                destroy_entity(registry, child);
            }
        }

        remove_parent(registry, entity);

        registry.destroy(entity);
    }
};
} // namespace varicle
