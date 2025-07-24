# sandbox_renderer/CMakeLists.txt
add_library(sandbox_renderer STATIC)

target_sources(sandbox_renderer
    PRIVATE
         src/vk_tools/vk_tools.cpp 
         src/window.cpp
         src/vulkan_wrapper/vulkan_instance.cpp
         src/vulkan_wrapper/vulkan_device.cpp
         src/vulkan_wrapper/vulkan_renderer.cpp
         src/vulkan_wrapper/vulkan_swapchain.cpp
         src/vulkan_wrapper/vulkan_buffer.cpp
         src/vulkan_wrapper/obj_model.cpp
     
 )


target_include_directories(sandbox_renderer
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

find_package(Vulkan REQUIRED)

# Link against required libraries
target_link_libraries(sandbox_renderer
    PUBLIC
        glfw
		glm
        spdlog
        Vulkan::Vulkan
        tinyobjloader
)