#pragma once
#include <variant>
#include <string>
#include <mutex>
#include <iostream>

struct Vec2 {
    float x = 0.0f;
    float y = 0.0f;

    bool operator==(const Vec2& o) const { return x == o.x && y == o.y; }
    bool operator!=(const Vec2& o) const { return !(*this == o); }
    Vec2 operator+(const Vec2& o) const { return { x + o.x, y + o.y }; }
    Vec2 operator-(const Vec2& o) const { return { x - o.x, y - o.y }; }
    Vec2 operator*(float scalar) const { return { x * scalar, y * scalar }; }
};

struct Vec3 {
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;

    bool operator==(const Vec3& o) const { return x == o.x && y == o.y && z == o.z; }
    bool operator!=(const Vec3& o) const { return !(*this == o); }
    Vec3 operator+(const Vec3& o) const { return { x + o.x, y + o.y, z + o.z }; }
    Vec3 operator-(const Vec3& o) const { return { x - o.x, y - o.y, z - o.z }; }
    Vec3 operator*(float scalar) const { return { x * scalar, y * scalar, z * scalar }; }
};

struct Vec4 {
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    float w = 1.0f;

    bool operator==(const Vec4& o) const { return x == o.x && y == o.y && z == o.z && w == o.w; }
    bool operator!=(const Vec4& o) const { return !(*this == o); }
    Vec4 operator+(const Vec4& o) const { return { x + o.x, y + o.y, z + o.z, w + o.w }; }
    Vec4 operator-(const Vec4& o) const { return { x - o.x, y - o.y, z - o.z, w - o.w }; }
    Vec4 operator*(float scalar) const { return { x * scalar, y * scalar, z * scalar, w * scalar }; }
};


// Standalone Interpolation Helpers
inline Vec2 Vec2Lerp(const Vec2& s, const Vec2& e, float a) { return { s.x + (e.x - s.x) * a, s.y + (e.y - s.y) * a }; }
inline Vec3 Vec3Lerp(const Vec3& s, const Vec3& e, float a) { return { s.x + (e.x - s.x) * a, s.y + (e.y - s.y) * a, s.z + (e.z - s.z) * a }; }
inline Vec4 Vec4Lerp(const Vec4& s, const Vec4& e, float a) { return { s.x + (e.x - s.x) * a, s.y + (e.y - s.y) * a, s.z + (e.z - s.z) * a, s.w + (e.w - s.w) * a }; }




enum class VariantType { Null, Float, Vector2, Vector3, Vector4, String };

class EngineVariant{

    public:
        using InternalVariant = std::variant<std::monostate,float,Vec2,Vec3,Vec4,std::string>;

        EngineVariant() : data(std::monostate{}), type(VariantType::Null){}
        EngineVariant(float v) : data(v), type(VariantType::Float){}
        EngineVariant(Vec2 v) : data(v), type(VariantType::Vector2){}
        EngineVariant(Vec3 v) : data(v), type(VariantType::Vector3){}
        EngineVariant(Vec4 v) : data(v), type(VariantType::Vector4){}
        EngineVariant(std::string v) : data(v), type(VariantType::String){}

        VariantType GetType() const { return type; }

        template<typename T>
            T Get() const {
                std::lock_guard<std::mutex> lock(v_mutex);
                return std::get<T>(data);
            }

        void Print() const {

            std::lock_guard<std::mutex> lock(v_mutex);
            std::cout << "[Variant " << TypeToString(type) << "]: ";
            std::visit([](auto &&arg){
                    using T = std::decay_t<decltype(arg)>;
                    if constexpr (std::is_same_v<T, std::monostate>) std::cout << "Null";
                    else if constexpr (std::is_same_v<T, float>) std::cout << arg;
                    else if constexpr (std::is_same_v<T, Vec2>) std::cout << "(" << arg.x << ", " << arg.y << ")";
                    else if constexpr (std::is_same_v<T, Vec3>) std::cout << "(" << arg.x << ", " << arg.y << ", " << arg.z << ")";
                    else if constexpr (std::is_same_v<T, Vec4>) std::cout << "(" << arg.x << ", " << arg.y << ", " << arg.z << ", " << arg.w << ")";
                    else if constexpr (std::is_same_v<T, std::string>) std::cout << "\"" << arg << "\"";

                    },data);

            std::cout << "\n";
        }

    private:
        InternalVariant data;
        VariantType type;
        mutable std::mutex v_mutex;

        static std::string TypeToString(VariantType t) {
            switch(t) {
                case VariantType::Float: return "Float";
                case VariantType::Vector2: return "Vector2";
                case VariantType::Vector3: return "Vector3";
                case VariantType::Vector4: return "Vector4";
                case VariantType::String: return "String";
                default: return "Null";
            }
        }

    friend class VariantOpManager;
};
