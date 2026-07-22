#pragma once

#include "engine-variant.hpp"

#include <entt/entt.hpp>
#include <functional>
#include <unordered_map>

using VariantGetter =
    std::function<EngineVariant(const entt::registry &, entt::entity)>;
using VariantSetter = std::function<void(entt::registry &, entt::entity,
                                         const EngineVariant &)>;

struct PropertyRef {
    uint32_t property_id;
    VariantSetter setter;
    VariantGetter getter;

    EngineVariant get(const entt::registry &reg, entt::entity e) const {
        return getter ? getter(reg, e) : EngineVariant();
    }

    void set(entt::registry &reg, entt::entity e,
             const EngineVariant &value) const {
        if (setter)
            setter(reg, e, value);
    }
};

class PropertyRegistry {
  public:
    template <typename Component, typename T>
    static PropertyRef bind_field(uint32_t prop_hash, T Component::*member) {
        return PropertyRef{.property_id = prop_hash,

                           .setter =
                               [member](entt::registry &reg, entt::entity e,
                                        const EngineVariant &val) {
                                   if (auto *comp = reg.try_get<Component>(e)) {
                                       (*comp).*member = val.Get<T>();
                                   }
                               },
                           .getter = [member](const entt::registry &reg,
                                              entt::entity e) -> EngineVariant {
                               if (auto *component =
                                       reg.try_get<Component>(e)) {
                                   return EngineVariant((*component).*member);
                               }
                               return EngineVariant();
                           }
        };
    }
};

class PropertyDatabase {
  private:
    std::unordered_map<uint32_t, PropertyRef> properites;

  public:
    void register_property(uint32_t prop_hash, PropertyRef ref) {
        properites[prop_hash] = std::move(ref);
    }

    EngineVariant get_value(const entt::registry &reg, entt::entity e,
                            uint32_t prop_hash) const {
        auto it = properites.find(prop_hash);
        if (it != properites.end()) {
            return it->second.get(reg, e);
        }
        return EngineVariant();
    }

    bool set_value(entt::registry &reg, entt::entity e,
                   uint32_t prop_hash, const EngineVariant &value) const {
        auto it = properites.find(prop_hash);
        if (it != properites.end()) {
            it->second.set(reg, e, value);
            return true;
        }
        return false;
    }
};
