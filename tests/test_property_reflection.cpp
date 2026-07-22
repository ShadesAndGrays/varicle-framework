#include <iostream>
#include <cassert>
#include "engine/ecs/bindings.hpp"
#include "engine/ecs/components.hpp"
#include "engine/core/engine-variant/engine-variant.hpp"
#include "engine/core/engine-variant/engine-variant-property.hpp"
#include "engine/core/engine-variant/engine-variant-property-id.hpp"
#include <entt/entt.hpp>


using namespace varicle;

int main() {
    std::cout << "[TEST] Starting Property Reflection & Type Safety Tests...\n";

    // Setup ECS Registry & Property DB
    entt::registry registry;
    PropertyDatabase propDB;
    register_all_component_properties(propDB);

    // Create an Entity with LocalTransform2D & Sprite
    entt::entity player = registry.create();
    registry.emplace<LocalTransform2D>(player, Vec2{10.0f, 20.0f}, 1.5f);
    registry.emplace<Sprite>(player,"",0.f,0.f,120.f,120.f,false,false,45.0f);

    // =========================================================================
    // TEST 1: Reading Values via PropertyID (Getter)
    // =========================================================================
    {
        Vec2 pos = propDB.get_value(registry,player,varicle::PropertyID::TransformPosition).get<Vec2>();
        float scale = propDB.get_value(registry,player,varicle::PropertyID::TransformScale).get<float>();
        float rot = propDB.get_value(registry,player,varicle::PropertyID::SpriteRotation).get<float>();

        assert(pos.x == 10.0f && pos.y == 20.0f && "Transform position getter failed!");
        assert(scale == 1.5f && "Transform scale getter failed!");
        assert(rot == 45.0f && "Sprite rotation getter failed!");

        std::cout << "  [PASS] Test 1: Getters retrieved correct values.\n";
    }

    // =========================================================================
    // TEST 2: Writing Values via PropertyID (Setter)
    // =========================================================================
    {
        propDB.set_value(registry,player,varicle::PropertyID::TransformPosition, Vec2{100.0f, 200.0f});
        std::cout << "setting value: " <<  (propDB.set_value(registry,player,varicle::PropertyID::SpriteRotation, 90.0f) ? "success" : "failed");
        propDB.set_value(registry,player,varicle::PropertyID::SpriteFlipH, true);

        // Verify the actual component struct in EnTT was mutated directly!
        const auto& transform = registry.get<LocalTransform2D>(player);
        const auto& sprite = registry.get<Sprite>(player);

        assert(transform.position.x == 100.0f && transform.position.y == 200.0f && "Position write failed!");
        assert(sprite.rotation == 90.0f && "Rotation write failed!");
        assert(sprite.flip_h == true && "FlipH write failed!");

        std::cout << "  [PASS] Test 2: Setters successfully mutated component struct.\n";
    }

    // =========================================================================
    // TEST 3: Type Safety Guard (Attempting Wrong Type Assignment)
    // =========================================================================
    {
        std::cout << "  [INFO] Expecting type safety warning below:\n";

        // Try to push a std::string into a float property (SpriteRotation)
        EngineVariant badType(std::string("WrongTypeData"));
        propDB.set_value(registry,player,varicle::PropertyID::SpriteRotation, badType);

        // Verify value was NOT modified because type mismatch was caught
        const auto& sprite = registry.get<Sprite>(player);
        assert(sprite.rotation == 90.0f && "Type safety guard failed! Wrong type was written!");

        std::cout << "  [PASS] Test 3: Type Safety Guard blocked invalid type write.\n";
    }

    std::cout << "\n[SUCCESS] All reflection tests passed successfully!\n";
    return 0;
}
