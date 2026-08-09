# vendor/raylib/CMakeLists.txt
cmake_minimum_required(VERSION 3.14)
project(raylib_vendored C)

# Select platform source based on target compiler
if(EMSCRIPTEN)
    set(PLATFORM_NAME "PLATFORM_WEB")
else()
    set(PLATFORM_NAME "PLATFORM_DESKTOP")
endif()

# Collect all Raylib C source files
file(GLOB RAYLIB_SOURCES CONFIGURE_DEPENDS "src/*.c")

# Create a static library target
add_library(raylib STATIC
    ${RAYLIB_SOURCES}
)

target_compile_definitions(raylib PUBLIC 
    ${PLATFORM_NAME}
    USE_EXTERNAL_GLFW  # Tells rcore.c to use the bundled GLFW platform backend
)

# Expose Raylib headers to your main engine target
target_include_directories(raylib PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/platforms"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/external"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/external/glfw/include"
)

# Platform-specific system libraries
if(WIN32)
    target_link_libraries(raylib PUBLIC winmm gdi32 opengl32)
elseif(APPLE)
    target_link_libraries(raylib PUBLIC "-framework OpenGL" "-framework Cocoa" "-framework IOKit" "-framework CoreVideo")
elseif(EMSCRIPTEN)
    # Emscripten links OpenGL/WebAudio flags automatically
else() # Linux
    target_link_libraries(raylib PUBLIC GL m pthread dl rt X11)
endif()
