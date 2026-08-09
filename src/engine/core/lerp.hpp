#pragma once

#include "engine/core/constants.hpp"
#include <algorithm>
#include <cmath>
#include <functional>

namespace varicle {

using EaseFunc = std::function<float(float)>;

class Ease {
  public:
    static inline float clamp01(float t) { return std::clamp(t, 0.0f, 1.0f); }

    static float linear(float t) { return clamp01(t); }

    static float quad_in(float t) {
        t = clamp01(t);
        return t * t;
    }

    static float cubic_in(float t) {
        t = clamp01(t);
        return t * t * t;
    }

    static float smoothstep(float t) {
        t = clamp01(t);
        return t * t * (3.0f - 2.0f * t);
    }

    static float power_out(float t, float k = 10.0f) {
        t = clamp01(t);
        const float top = 1.0f - std::exp2f(-k * t);
        const float bottom = 1.0f - std::exp2f(-k);
        return top / bottom;
    }

    static float bounce_out(float t, float damping = 8.0f,
                            float frequency = 3.0f) {
        t = clamp01(t);
        const float decay = std::exp2f(-damping * t);
        const float wave =
            std::abs(std::cos((0.5f + frequency) * constants::pi * t));
        return 1.0f - (decay * wave);
    }
};

class LerpUtil {

  public:
    // Core Linear Interpolation (No Easing)
    template <typename T, typename FloatType>
    // can the {} be evaluated and can -> return be converted back to T
        requires requires(T a, T b, FloatType t) {
            { (b - a) * t } -> std::convertible_to<T>;
            { a + (b - a) * t } -> std::convertible_to<T>;
        }
    static T lerp(T a, T b, FloatType t) {
        return a + (b - a) * t;
    }

    // Discrete
    template <typename T> static T discrete(T a, T b, float t) {
        return t < 1.0f ? a : b;
    }

    // Applied Easing any func
    template <typename T, typename EaseFunc>
    static T eased_lerp(T a, T b, float alpha, EaseFunc ease_fn) {
        return LerpUtil::lerp(a, b, ease_fn(alpha));
    }
};

} // namespace varicle
