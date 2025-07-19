# external/CMakeLists.txt
cmake_minimum_required(VERSION 3.24)
project(external)

# GLFW
add_subdirectory(glfw)

# GLM is header-only, so create an interface library for it
add_library(glm INTERFACE)
target_include_directories(glm INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/glm")


# Volk (single-header Vulkan loader)
add_library(volk STATIC volk/volk.c)
target_include_directories(volk PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/volk")

# Before using Volk, we still need Vulkan SDK available for headers/libs
find_package(Vulkan REQUIRED)
target_link_libraries(volk PUBLIC Vulkan::Vulkan)

# spdlog
add_subdirectory(spdlog)