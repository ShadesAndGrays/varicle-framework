cmake_minimum_required(VERSION 3.25)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(farm-space LANGUAGES CXX)

add_executable(${PROJECT_NAME} src/main.cpp)


target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/dist/include
)
target_link_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_SOURCE_DIR}/dist/lib
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    varicle
    raylib
    assetpacker
)

if(EMSCRIPTEN)
    # Output an HTML page instead of a raw binary
    set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_NAME "index"
        SUFFIX ".html"
    )

    # Pass Emscripten linker flags
    target_link_options(${PROJECT_NAME} PRIVATE
        "-sUSE_GLFW=3"                  # Needed for Raylib web builds
        "-sASYNCIFY"                    # Allows main loop to yield to the browser
        "--shell-file" "${CMAKE_CURRENT_SOURCE_DIR}/html/shell_custom.html" # (Optional) Custom HTML shell
        # Pre-pack your assets directory into the WebAssembly virtual filesystem
        "--preload-file" "${CMAKE_CURRENT_BINARY_DIR}/data.dat@/data.dat"
    )

elseif(WIN32)
    target_link_libraries(farm-space PRIVATE winmm opengl32 gdi32)
endif()

add_custom_target(run
    COMMAND ${PROJECT_NAME}
    DEPENDS ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

