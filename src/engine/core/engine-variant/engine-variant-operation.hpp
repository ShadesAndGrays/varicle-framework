#pragma once

#include "engine-variant.hpp"

namespace varicle {

template <class... Ts> struct overloaded : Ts... {
    using Ts::operator()...;
};
template <class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

enum class OpType {
    Assign,   // Replace the old value entirely
    Add,      // Add to the current value
    Multiply, // Add to the current value
    Lerp      // Smoothly blend toward a value
};

struct VariantOpRequest {
    EngineVariant *target; // The variable we want to change
    OpType operation;      // How we want to change it
    EngineVariant operand; // The value we are using to make the change
    float alpha;           // Used ONLY for Lerp (0.0 to 1.0)
};

class VariantOpManager {

  public:
    VariantOpManager() {}
    void ExecuteOperation(const VariantOpRequest &req) {

        if (req.target == nullptr)
            return;

        switch (req.operation) {

        case OpType::Assign:
            req.target->data = req.operand.data;
            break;
        case OpType::Add:
            req.target->data = std::visit(
                overloaded{
                    [](float p, float n) -> EngineVariant::InternalVariant {
                        return p + n;
                    },
                    [](Vec2 p, Vec2 n) -> EngineVariant::InternalVariant {
                        return p + n;
                    },
                    [](Vec3 p, Vec3 n) -> EngineVariant::InternalVariant {
                        return p + n;
                    },
                    [](Vec4 p, Vec4 n) -> EngineVariant::InternalVariant {
                        return p + n;
                    },

                    // Fallback
                    [](auto p, auto n) -> EngineVariant::InternalVariant {
                        return p;
                    },
                },
                req.target->data, req.operand.data);
            break;

        case OpType::Lerp:
            req.target->data = std::visit(
                overloaded{
                    [&](float p, float n) -> EngineVariant::InternalVariant {
                        return p + (n - p) * req.alpha;
                    },
                    [&](Vec2 p, Vec2 n) -> EngineVariant::InternalVariant {
                        return Vec2Lerp(p, n, req.alpha);
                    },
                    [&](Vec3 p, Vec3 n) -> EngineVariant::InternalVariant {
                        return Vec3Lerp(p, n, req.alpha);
                    },
                    [&](Vec4 p, Vec4 n) -> EngineVariant::InternalVariant {
                        return Vec4Lerp(p, n, req.alpha);
                    },
                    [&](const std::string &p, const std::string &n)
                        -> EngineVariant::InternalVariant {
                        return req.alpha >= 0.5f
                                   ? n
                                   : p; // Discrete switch for strings
                    },

                    // Fallback
                    [](auto p, auto n) -> EngineVariant::InternalVariant {
                        return p;
                    }},
                req.target->data, req.operand.data);
            break;

        case OpType::Multiply:
            req.target->data = std::visit(
                overloaded{
                    [](float p, float n) -> EngineVariant::InternalVariant {
                        return p * n;
                    },
                    [](Vec2 p, float n) -> EngineVariant::InternalVariant {
                        return p * n;
                    }, // Scale a vector!
                    [](auto p, auto n) -> EngineVariant::InternalVariant {
                        return p;
                    }},
                req.target->data, req.operand.data);
            break;
        }
    }
};

} // namespace varicle
