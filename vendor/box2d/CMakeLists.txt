cmake_minimum_required(VERSION 3.16)

project(box2d C)

# Find all C source files inside Box2D's src/ directory
file(GLOB_RECURSE BOX2D_SOURCES CONFIGURE_DEPENDS "src/*.c")

# Create static library
add_library(box2d STATIC ${BOX2D_SOURCES})

# Expose the include folder so your engine can write #include <box2d/box2d.h>
target_include_directories(box2d PUBLIC include)

# Ensure modern C standard (C11 / C23)
set_target_properties(box2d PROPERTIES C_STANDARD 11 C_STANDARD_REQUIRED ON)
