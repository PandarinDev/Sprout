cmake_minimum_required(VERSION 3.8)
project(Sprout)

set(CMAKE_CXX_STANDARD 17)
file(GLOB_RECURSE SPROUT_SOURCE_FILES "Source/*.cpp" "Source/*.c")
file(GLOB_RECURSE SPROUT_HEADER_FILES "Include/*.h")

add_executable(Sprout ${SPROUT_SOURCE_FILES} ${SPROUT_HEADER_FILES})
target_include_directories(Sprout PUBLIC "Include")

# Dependencies
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMake/Modules")
find_package(glfw3 REQUIRED)
find_package(glm CONFIG REQUIRED)

target_include_directories(Sprout PRIVATE ${GLFW3_INCLUDE_DIR})
target_link_libraries(Sprout GLFW::glfw3 glm)