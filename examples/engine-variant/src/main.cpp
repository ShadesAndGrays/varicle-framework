#include "engine/core/application.hpp"
#include "engine/core/color.hpp"
#include "engine/core/engine-variant/engine-variant-operation.hpp"
#include "engine/core/engine-variant/engine-variant.hpp"

#include <entt/entt.hpp>
#include <format>
#include <raylib.h>

namespace v = varicle;

int main() {
    v::EngineVariant name("Hero");
    v::EngineVariant address(std::string("12 Man way"));
    v::EngineVariant age(12);
    v::EngineVariant height(12.0f);
    v::EngineVariant is_rich(false);
    v::EngineVariant coord(v::Vec2{1.0f, 2.0f});
    v::EngineVariant coord3(v::Vec3{1.0f, 2.0f, 3.0f});
    v::EngineVariant coord4(v::Vec4{1.0f, 2.0f, 3.0f, 4.0f});
    v::EngineVariant color(v::Color::Red());
    entt::registry reg;
    v::EngineVariant entity(reg.create());

    std::cout << name << std::endl;
    std::cout << address << std::endl;
    std::cout << age << std::endl;
    std::cout << height << std::endl;
    std::cout << is_rich << std::endl;
    std::cout << coord << std::endl;
    std::cout << coord3 << std::endl;
    std::cout << coord4 << std::endl;
    std::cout << color << std::endl;
    std::cout << entity << std::endl;

    v::EngineVariant vec1(v::Vec2{1.0f, 1.0f});
    v::EngineVariant vec2(v::Vec2{2.0f, 1.0f});

    v::EngineVariant vec3_result =
        v::VariantOpManager::Execute({vec1, v::op::Add{vec2}});

    std::cout << std::format("{} + {} = {}", vec1.to_string(), vec2.to_string(),
                             vec3_result.to_string())
              << std::endl;

    v::EngineVariant vec4(v::Vec3{2.0f, 1.0f, 1.0f});

    v::EngineVariant vec4_result =
        v::VariantOpManager::Execute({vec1, v::op::Add{vec4}});

    std::cout << "Execution not possible result same as vec1: " << vec1
              << " vec4_result: " << vec4_result << std::endl;

    v::EngineVariant a(10.0f);
    v::EngineVariant b(33.0f);

    for (int step = 0; step <= 10; step += 1) {
        float i = step * 0.1f;
        std::cout << i << ": "
                  << v::VariantOpManager::Execute({a, v::op::Lerp{b, i}})
                  << " ";
    }
    std::cout << std::endl;

    v::EngineVariant vec_a(v::Vec2{10.0f,20.0f});
    v::EngineVariant vec_b(v::Vec2{33.0f,40.0f});

    for (int step = 0; step <= 10; step += 1) {
        float i = step * 0.1f;
        std::cout << i << ": "
                  << v::VariantOpManager::Execute({vec_a, v::op::Lerp{vec_b, i,v::Ease::quad_in}})
                  << " ";
    }
    std::cout << std::endl;


    return 0;
}
