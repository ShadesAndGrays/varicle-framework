#pragma once
#include <cstdint>

namespace varicle {
struct Color {
    uint8_t r = 255;
    uint8_t g = 255;
    uint8_t b = 255;
    uint8_t a = 255;

    // Common default presets
    static constexpr Color White() { return {255, 255, 255, 255}; }
    static constexpr Color Red() { return {255, 0, 0, 255}; }

static constexpr Color Orange() { return {255, 165, 0, 255}; }

static constexpr Color Yellow() { return {255, 255, 0, 255}; }

static constexpr Color Green()  { return {0, 255, 0, 255}; }

static constexpr Color Blue()   { return {0, 0, 255, 255}; }

static constexpr Color Purple() { return {200, 122, 255, 255}; }

};
} // namespace varicle
