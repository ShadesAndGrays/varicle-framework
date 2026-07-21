cmake_minimum_required(VERSION 4.4.0)


project(my_app LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# set(CMAKE_CXX_STANDARD_REQUIRED ON)

file( GLOB_RECURSE
    SRC
    CONFIGURE
    "src/*cpp"
    "src/*.hpp"
)

message(VERBOSE ${SRC})

add_executable(my_app ${SRC})

INCLUDE_DIRECTORIES("src")

set_target_properties( my_app PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENXSIONS OFF

)

target_link_libraries(my_app PRIVATE stdc++exp )

