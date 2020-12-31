cmake_minimum_required(VERSION 3.14)

project(Game2D)

add_definitions(-DPROJECT_NAME="${PROJECT_NAME}")

add_subdirectory(Game)
add_subdirectory(lib)