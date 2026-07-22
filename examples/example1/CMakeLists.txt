cmake_minimum_required(VERSION 3.25)

project(example1 LANGUAGES CXX)

file(GLOB_RECURSE SRCS "src/*.cpp")

MESSAGE(STATUS ${SRCS})


add_executable(${PROJECT_NAME} ${SRCS})

target_include_directories(${PROJECT_NAME} PRIVATE src)

target_link_libraries(${PROJECT_NAME} PRIVATE varicle_lib)
