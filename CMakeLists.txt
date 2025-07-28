# Root CMakeLists.txt 
cmake_minimum_required(VERSION 3.24)
project(vk_sandbox LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Enable warnings
if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()


# Global definitions
add_definitions(-DGLM_ENABLE_EXPERIMENTAL) # GLM experimental
add_compile_definitions(PROJECT_ROOT_DIR="${CMAKE_CURRENT_SOURCE_DIR}") # Project root 

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# External libraries
add_subdirectory(external)

# Core targets
add_subdirectory(sandbox_renderer)
add_subdirectory(sandbox_engine)
add_subdirectory(sandbox_game)
add_subdirectory(core_interfaces)

# Shader compilation

file(GLOB SHADER_FILES 
    "${CMAKE_CURRENT_SOURCE_DIR}/res/shaders/*.vert" 
    "${CMAKE_CURRENT_SOURCE_DIR}/res/shaders/*.frag"
)

set(SPIRV_OUTPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/res/shaders/spirV")
file(MAKE_DIRECTORY ${SPIRV_OUTPUT_DIR})

foreach(SHADER_FILE ${SHADER_FILES})
    get_filename_component(FILE_NAME ${SHADER_FILE} NAME)
    add_custom_command(
        OUTPUT ${SPIRV_OUTPUT_DIR}/${FILE_NAME}.spv
        COMMAND ${CMAKE_COMMAND} -E echo "Compiling shader: ${FILE_NAME}"
        COMMAND glslangValidator -V --target-env vulkan1.3 ${SHADER_FILE} -o ${SPIRV_OUTPUT_DIR}/${FILE_NAME}.spv
        DEPENDS ${SHADER_FILE}
        COMMENT "Compiling ${FILE_NAME} to SPIR-V"
    )
    list(APPEND SPIRV_BINARIES ${SPIRV_OUTPUT_DIR}/${FILE_NAME}.spv)
endforeach()

add_custom_target(CompileShaders ALL DEPENDS ${SPIRV_BINARIES})
add_dependencies(sandbox_game CompileShaders)
