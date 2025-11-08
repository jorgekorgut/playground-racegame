cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME RaceGame)

project(${PROJECT_NAME})

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

list(APPEND SOURCES src/main.cpp)

include_directories(${GLM_ROOT})

# Engine Configuration ====================================================================================
set(ENGINE_ROOT "" CACHE PATH "Path to ENGINE root directory (should contain src/)")
if(NOT EXISTS "${ENGINE_ROOT}/src/Engine.h")
    message(FATAL_ERROR "Could not find Engine in '${ENGINE_ROOT}'. Please set Engine_ROOT to the correct directory.")
endif()
include_directories(${ENGINE_ROOT}/src)
add_subdirectory(${ENGINE_ROOT} "${ENGINE_ROOT}/build")
# =========================================================================================================

set(SRC_ROOT "src")
set(SHADER_ROOT "shaders")

file(GLOB_RECURSE SHADER_FILES ${SHADER_ROOT}/**.frag ${SHADER_ROOT}/*.frag ${SHADER_ROOT}/**.vert ${SHADER_ROOT}/*.vert)
file(GLOB_RECURSE HEADER_FILES ${SRC_ROOT}/**.h ${SRC_ROOT}/*.h)
file(GLOB_RECURSE SOURCE_FILES ${SRC_ROOT}/**.cpp ${SRC_ROOT}/*.cpp)

include_directories(${SRC_ROOT})

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES} ${SHADER_FILES} ${LIBS_FILES} "README.md" ".clang-format")

source_group(TREE ${CMAKE_SOURCE_DIR} FILES ${SHADER_FILES})
source_group(TREE ${CMAKE_SOURCE_DIR} FILES ${LIBS_FILES})
source_group(TREE ${CMAKE_SOURCE_DIR} FILES ${HEADER_FILES})
source_group(TREE ${CMAKE_SOURCE_DIR} FILES ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE "${ENGINE_ROOT}/build/Debug/Engine.lib")
target_link_libraries(${PROJECT_NAME} PUBLIC "${GLFW_ROOT}/lib/glfw3.lib")

# sets the Editor project as the default startup project in Visual Studio
set_property(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}" PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

# copy resources to build folder
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/resources ${CMAKE_BINARY_DIR}/$<CONFIG>/resources)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/resources ${CMAKE_BINARY_DIR}/resources)


# copy engine resources to build folder
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E create_symlink "${ENGINE_ROOT}/shaders" "${CMAKE_BINARY_DIR}/$<CONFIG>/engine_shaders")
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E create_symlink "${ENGINE_ROOT}/shaders" "${CMAKE_BINARY_DIR}/engine_shaders")

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E create_symlink "${ENGINE_ROOT}/resources" "${CMAKE_BINARY_DIR}/$<CONFIG>/engine_resources")
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E create_symlink "${ENGINE_ROOT}/resources" "${CMAKE_BINARY_DIR}/engine_resources")
