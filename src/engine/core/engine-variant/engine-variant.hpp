#pragma once
#include <iostream>
#include <string>
#include <variant>

namespace varicle {
// Overload helper pattern
template <class... Ts> struct Overloaded : Ts... {
    using Ts::operator()...;
};
template <class... Ts> Overloaded(Ts...) -> Overloaded<Ts...>;

struct Vec2 {
    float x = 0.0f;
    float y = 0.0f;

    bool operator==(const Vec2 &o) const { return x == o.x && y == o.y; }
    bool operator!=(const Vec2 &o) const { return !(*this == o); }
    Vec2 operator+(const Vec2 &o) const { return {x + o.x, y + o.y}; }
    Vec2 operator-(const Vec2 &o) const { return {x - o.x, y - o.y}; }
    Vec2 operator*(float scalar) const { return {x * scalar, y * scalar}; }
};

struct Vec3 {
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;

    bool operator==(const Vec3 &o) const {
        return x == o.x && y == o.y && z == o.z;
    }
    bool operator!=(const Vec3 &o) const { return !(*this == o); }
    Vec3 operator+(const Vec3 &o) const { return {x + o.x, y + o.y, z + o.z}; }
    Vec3 operator-(const Vec3 &o) const { return {x - o.x, y - o.y, z - o.z}; }
    Vec3 operator*(float scalar) const {
        return {x * scalar, y * scalar, z * scalar};
    }
};

struct Vec4 {
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    float w = 1.0f;

    bool operator==(const Vec4 &o) const {
        return x == o.x && y == o.y && z == o.z && w == o.w;
    }
    bool operator!=(const Vec4 &o) const { return !(*this == o); }
    Vec4 operator+(const Vec4 &o) const {
        return {x + o.x, y + o.y, z + o.z, w + o.w};
    }
    Vec4 operator-(const Vec4 &o) const {
        return {x - o.x, y - o.y, z - o.z, w - o.w};
    }
    Vec4 operator*(float scalar) const {
        return {x * scalar, y * scalar, z * scalar, w * scalar};
    }
};

// Standalone Interpolation Helpers
inline Vec2 Vec2Lerp(const Vec2 &s, const Vec2 &e, float a) {
    return {s.x + (e.x - s.x) * a, s.y + (e.y - s.y) * a};
}
inline Vec3 Vec3Lerp(const Vec3 &s, const Vec3 &e, float a) {
    return {s.x + (e.x - s.x) * a, s.y + (e.y - s.y) * a,
            s.z + (e.z - s.z) * a};
}
inline Vec4 Vec4Lerp(const Vec4 &s, const Vec4 &e, float a) {
    return {s.x + (e.x - s.x) * a, s.y + (e.y - s.y) * a, s.z + (e.z - s.z) * a,
            s.w + (e.w - s.w) * a};
}

enum class VariantType { Null, Float, Vector2, Vector3, Vector4, String };

class EngineVariant {

  public:
    using InternalVariant = std::variant<std::monostate, float, Vec2, Vec3,
                                         Vec4, std::string, bool>;

    EngineVariant() : data(std::monostate{}) {}
    EngineVariant(float v) : data(v) {}
    EngineVariant(Vec2 v) : data(v) {}
    EngineVariant(Vec3 v) : data(v) {}
    EngineVariant(Vec4 v) : data(v) {}
    EngineVariant(std::string v) : data(v) {}
    EngineVariant(bool v) : data(v) {}

    template <typename T> T Get() const { return std::get<T>(data); }
    template <typename T> T *TryGet() { return std::get_if<T>(&data); }

    std::string ToString() const {
        return std::visit(
            Overloaded{[](std::monostate) { return std::string("!"); },
                       [](float v) { return std::to_string(v); },
                       [](const Vec2 &v) {
                           return "(" + std::to_string(v.x) + ", " +
                                  std::to_string(v.y) + ")";
                       },
                       [](const Vec3 &v) {
                           return "(" + std::to_string(v.x) + ", " +
                                  std::to_string(v.y) + ", " +
                                  std::to_string(v.z) + ")";
                       },
                       [](const Vec4 &v) {
                           return "(" + std::to_string(v.x) + ", " +
                                  std::to_string(v.y) + ", " +
                                  std::to_string(v.z) + ", " +
                                  std::to_string(v.w) + ")";
                       },
                       [](const std::string &s) { return s; },
                       [](const bool &b) {
                           return std::string(b ? "true" : "false");
                       }},
            data);
    }

    friend std::ostream &operator<<(std::ostream &os,
                                    const EngineVariant &variant) {
        return os << variant.GetTypeName() << variant.ToString();
    }

  private:
    InternalVariant data;

    std::string GetTypeName() const {
        return std::visit(
            [](auto &&arg) -> std::string {
                using T = std::decay_t<decltype(arg)>;
                if constexpr (std::is_same_v<T, std::monostate>)
                    return "Null";
                else if constexpr (std::is_same_v<T, float>)
                    return "Float";
                else if constexpr (std::is_same_v<T, Vec2>)
                    return "Vec2";
                else if constexpr (std::is_same_v<T, Vec3>)
                    return "Vec3";
                else if constexpr (std::is_same_v<T, Vec4>)
                    return "Vec4";
                else if constexpr (std::is_same_v<T, std::string>)
                    return "String";
                else if constexpr (std::is_same_v<T, bool>)
                    return "Bool";
                else
                    return "Unknown";
            },
            data);
    }

    friend class VariantOpManager;
};
} // namespace varicle
