# Root CMakeLists.txt 
#cmake_minimum_required(VERSION 3.24)
#project(gpu_sandbox LANGUAGES CXX)
cmake_minimum_required(VERSION 3.16)
project(SceneFoundry_gpu_sandbox CXX)

#
##set(CMAKE_CXX_STANDARD 20)
##set(CMAKE_CXX_STANDARD_REQUIRED ON)
##set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
#
## Enable warnings
##if (MSVC)
# #   add_compile_options(/W4)
##else()
# #   add_compile_options(-Wall -Wextra -Wpedantic)
##endif()
#
#
## Global definitions
#add_definitions(-DGLM_ENABLE_EXPERIMENTAL) # GLM experimental
##add_compile_definitions(PROJECT_ROOT_DIR="${CMAKE_CURRENT_SOURCE_DIR}") # Project root
#
## Set output directories
##set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
##set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
##set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
#
### External libraries
##add_subdirectory(external)
##
### Core targets
##add_subdirectory(sandbox_renderer)
##add_subdirectory(sandbox_engine)
##add_subdirectory(sandbox_game)
##add_subdirectory(core_interfaces)
#
## Shader compilation
#
##file(GLOB SHADER_FILES
# #   "${CMAKE_CURRENT_SOURCE_DIR}/res/shaders/*.vert"
#  #  "${CMAKE_CURRENT_SOURCE_DIR}/res/shaders/*.frag"
#   #)
#
##set(SPIRV_OUTPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/res/shaders/spirV")
##file(MAKE_DIRECTORY ${SPIRV_OUTPUT_DIR})
##
##foreach(SHADER_FILE ${SHADER_FILES})
##    get_filename_component(FILE_NAME ${SHADER_FILE} NAME)
##    add_custom_command(
##        OUTPUT ${SPIRV_OUTPUT_DIR}/${FILE_NAME}.spv
##        COMMAND ${CMAKE_COMMAND} -E echo "Compiling shader: ${FILE_NAME}"
##        COMMAND glslangValidator -V --target-env vulkan1.3 ${SHADER_FILE} -o ${SPIRV_OUTPUT_DIR}/${FILE_NAME}.spv
##        DEPENDS ${SHADER_FILE}
##        COMMENT "Compiling ${FILE_NAME} to SPIR-V"
##    )
##    list(APPEND SPIRV_BINARIES ${SPIRV_OUTPUT_DIR}/${FILE_NAME}.spv)
##endforeach()
##
##add_custom_target(CompileShaders ALL DEPENDS ${SPIRV_BINARIES})
##
#
##cmake_minimum_required(VERSION 3.16)
##project(app_app CXX)
#

list(APPEND library_source
        _.cpp
        _.h
        ##_library.h
        #_factory.h
        graphics3d/main_scene.cpp
        graphics3d/main_scene.h
        graphics3d/point_light_system.cpp
        graphics3d/point_light_system.h
        graphics3d/simple_render_system.cpp
        graphics3d/simple_render_system.h
        application.cpp
        application.h
        document.cpp
        document.h
        framework.cpp
        framework.h
        impact.cpp
        impact.h
        main_frame.cpp
        main_frame.h
        pane_impact.cpp
        pane_impact.h
)


list(APPEND library_references
        acme
        apex
        aqua
        aura
        axis
        berg
        bred
        core
        sandbox
        sandbox_renderer
        sandbox_engine
)


add_library(${PROJECT_NAME} SHARED ${library_source}
        ../sandbox/_types.cpp)
add_library(static_${PROJECT_NAME} STATIC ${library_source})




if(${LINUX} OR ${__BSD__})


    add_custom_command(
            OUTPUT ${PROJECT_SOURCE_DIR}/.link_object/_matter.zip.o
            COMMAND ${APPLICATION_BUILD_HELPER_BINARY} --prepare-application ${PROJECT_SOURCE_DIR}
            COMMENT "Generating ${PROJECT_SOURCE_DIR}/.link_object/_matter.zip.o"
    )

    target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/.link_object/_matter.zip.o)

endif()




if (NOT ${NO_PRECOMPILED_HEADER})

    target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)
    target_precompile_headers(static_${PROJECT_NAME} PRIVATE framework.h)

endif ()


set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)


    target_compile_options(${PROJECT_NAME} PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(${PROJECT_NAME} PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(${PROJECT_NAME} PRIVATE "/SUBSYSTEM:WINDOWS")
    target_link_libraries(${PROJECT_NAME} PRIVATE ${library_references} ${global_library_references})


elseif (${LINUX} OR ${__BSD__} OR ${ANDROID})


    target_link_libraries(${PROJECT_NAME} PRIVATE ${library_references} ${global_library_references})
    target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)
    # target_link_options(static_${PROJECT_NAME} PRIVATE --whole-archive)

    message(STATUS "(5) PKGCONFIG_LIBRARIES is " ${${PROJECT_NAME}_PKGCONFIG_LIBRARIES})


endif ()


add_dependencies(${PROJECT_NAME} apex_${OPERATING_SYSTEM_NAME})
add_dependencies(${PROJECT_NAME} ${default_node})
add_dependencies(${PROJECT_NAME} ${default_draw2d})


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)


target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})
target_include_directories(static_${PROJECT_NAME} PRIVATE ${library_include_directories})


target_compile_definitions(${PROJECT_NAME} PRIVATE _${PROJECT_NAME}_project)


add_subdirectory(__implement)









list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})
target_include_directories(static_${PROJECT_NAME} PRIVATE ${library_include_directories})


target_compile_definitions(${PROJECT_NAME} PRIVATE _${PROJECT_NAME}_project)




