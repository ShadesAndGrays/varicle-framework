cmake_minimum_required(VERSION 3.25)

project(varicle LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    # Default install location: <your-project-folder>/dist
    set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/dist" CACHE PATH "Local export directory" FORCE)
endif()

file( GLOB_RECURSE
    SRC
    CONFIGURE
    "src/*cpp"
    "src/*.hpp"
)



#------------------------------------------------------------------------------------------
# DiSt
#------------------------------------------------------------------------------------------
if(BUILD_FOR_WEB OR EMSCRIPTEN)
    set(DIST_PLATFORM "web")
else()
    set(DIST_PLATFORM "desktop")
endif()

set(DIST_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dist/${DIST_PLATFORM}")

#------------------------------------------------------------------------------------------
# Subdirectories
#------------------------------------------------------------------------------------------

set(BUILD_EXAMPLES OFF)
add_subdirectory(vendor/raylib)
add_subdirectory(vendor/asset-packer)


#------------------------------------------------------------------------------------------
# HEADERS AND SOURCE FILES 
#------------------------------------------------------------------------------------------

#ImGui
set(IMGUI_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui")

add_library(imgui STATIC
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
)

# target_include_directories(imgui PUBLIC ${IMGUI_DIR})

file(GLOB IMGUI_HEADERS
    CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/*.h"
)

target_include_directories(imgui PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/vendor/imGui>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)


target_sources(imgui INTERFACE
    FILE_SET HEADERS
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/vendor/
    FILES ${IMGUI_HEADERS}
)


# rlImGui

file(GLOB RLIMGUI_HEADERS
    CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/vendor/rlImGui/*.h"
)

set(RLIMGUI_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vendor/rlImGui")

add_library(rlImGui STATIC
    ${RLIMGUI_DIR}/rlImGui.cpp
)

# target_include_directories(rlImGui PUBLIC ${RLIMGUI_DIR})

target_link_libraries(rlImGui PUBLIC imgui raylib)


target_include_directories(rlImGui PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/vendor/rlImGui>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_sources(rlImGui INTERFACE
    FILE_SET HEADERS
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/vendor/
    FILES ${RLIMGUI_HEADERS}
)
#------------------------------------------------------------------------------------------
# Framework Library
#------------------------------------------------------------------------------------------

include(GNUInstallDirs)

file( GLOB_RECURSE
    ENGINE_SRC
    CONFIGURE
    "src/engine/*cpp"
    "src/engine/*.hpp"
)

add_library(${PROJECT_NAME}_lib ${ENGINE_SRC})


set_target_properties(${PROJECT_NAME}_lib PROPERTIES
        OUTPUT_NAME "varicle"
        )

target_include_directories(${PROJECT_NAME}_lib PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/vendor/entt>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(${PROJECT_NAME}_lib PUBLIC
    AssetPacker::assetpacker
    rlImGui
    imgui
    raylib
)

target_sources(${PROJECT_NAME}_lib PUBLIC
    FILE_SET HEADERS
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/src/
    FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/engine
)

# FRAMEWORK DEPENDECIES

#entt

add_library(entt INTERFACE)

target_include_directories(entt INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/vendor/entt>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_sources(entt INTERFACE
    FILE_SET HEADERS
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/vendor/entt
    FILES ${CMAKE_CURRENT_SOURCE_DIR}/vendor/entt/entt/entt.hpp
)

#json
add_library(json INTERFACE)

target_include_directories(json INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/vendor/json>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>/json
)

target_sources(json INTERFACE
    FILE_SET HEADERS
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/vendor/json
    FILES ${CMAKE_CURRENT_SOURCE_DIR}/vendor/json/json.hpp
)


install(TARGETS ${PROJECT_NAME}_lib raylib entt json assetpacker_lib imgui rlImGui
    EXPORT ${PROJECT_NAME}Targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}   # Static libs (.a / .lib)
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}   # Shared libs (.so / .dylib)
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}   # Windows DLLs (.dll)
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/engine
    FILE_SET HEADERS DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(EXPORT ${PROJECT_NAME}Targets
    FILE ${PROJECT_NAME}Targets.cmake
    NAMESPACE ${PROJECT_NAME}::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)


# 2. GENERATE the Config file (THIS IS THE MISSING PIECE!)
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/varicleConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/varicleConfig.cmake"
    INSTALL_DESTINATION lib/cmake/varicle
)

# 3. INSTALL the Config file alongside varicleTargets.cmake
install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/varicleConfig.cmake"
    DESTINATION lib/cmake/varicle
)

#------------------------------------------------------------------------------------------
# Executable
#------------------------------------------------------------------------------------------

add_executable(${PROJECT_NAME} ${SRC})


# Export ImGui headers so anything linking to 'imgui' gets them automatically
target_include_directories(${PROJECT_NAME} PRIVATE vendor/entt src)

target_link_libraries(${PROJECT_NAME} PRIVATE
    AssetPacker::assetpacker
    rlImGui
    imgui
    raylib
)


#------------------------------------------------------------------------------------------
# Make Assets
#------------------------------------------------------------------------------------------

set(BUILD_ASSET_DIR "${CMAKE_CURRENT_BINARY_DIR}/assets")
set(PACKED_DATA_FILE "${CMAKE_CURRENT_BINARY_DIR}/data.dat")

add_custom_target( pack-asset
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/assets"
            "${BUILD_ASSET_DIR}"


    # 2. Pass relative paths to assetpacker!
    # Because WORKING_DIRECTORY is ${CMAKE_CURRENT_BINARY_DIR},
    # 'assets' resolves to './assets' and 'data.dat' resolves to './data.dat'

    # Set execution context so relative paths inside assetpacker work
    WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"

    COMMAND AssetPacker::packer "assets/"

    DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/assets" AssetPacker::packer
    COMMENT "Copying assets folder and packing via relative paths..."
    VERBATIM

)


# ------------------------------------------------------------------------------
# WebAssembly / Emscripten Configurations
# ------------------------------------------------------------------------------

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

endif()

add_custom_target( run
    COMMAND ${PROJECT_NAME}
    DEPENDS ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

enable_testing()
add_subdirectory(tests)
