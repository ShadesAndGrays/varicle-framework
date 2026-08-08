cmake_minimum_required(VERSION 3.25)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # Generates compile_commands.json

cmake_path(GET CMAKE_CURRENT_SOURCE_DIR FILENAME PROJEC_DIR_NAME ) # Use folder name as project name

project(${PROJEC_DIR_NAME} LANGUAGES CXX)

add_subdirectory(varicle) # This adds and exposes varicle as a dependency

file (GLOB_RECURSE SRCS "src/*.cpp")

add_executable(${PROJECT_NAME} ${SRCS})

target_link_libraries(${PROJECT_NAME} PRIVATE varicle_lib)

# If compiling for web
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
    target_link_libraries(${PROJECT_NAME} PRIVATE winmm opengl32 gdi32)
endif()

# custom run binary command 
# add_custom_target(run
#     COMMAND ${PROJECT_NAME}
#     DEPENDS ${PROJECT_NAME}
#     WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
# )

# add_custom_target(pack-asset
#     COMMAND ${CMAKE_BINARY_DIR}/vendor/asset-packer/assetpacker.exe assets/
#     DEPENDS ${PROJECT_NAME}
#     WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
# )


