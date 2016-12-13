# This CMake script is designed for CLion IDE and QTCreator projects on Windows
# It should find bundled binary dependencies automatically when using MinGW compiler
# On Linux and Mac the dependencies (glm, glew, glfw) need to be installed manually

cmake_minimum_required(VERSION 3.1)
project(ppgso CXX)

#
# CONFIGURATION
#

# Basic CMake settings
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/_install)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# Add custom target for installation in CLion

add_custom_target(run_install COMMAND ${CMAKE_MAKE_PROGRAM} install)

# Use generate_shader function to convert .glsl sources to C++ headers
include(shaders)

#
# DEPENDENCIES
#

# Set up external dependencies for Windows users
if (MINGW)
  set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "${CMAKE_SOURCE_DIR}/dependencies/include/")
  set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${CMAKE_SOURCE_DIR}/dependencies/lib/mingw")
elseif (MSVC)
  set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "${CMAKE_SOURCE_DIR}/dependencies/include/")
  set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${CMAKE_SOURCE_DIR}/dependencies/lib/vc2015")
  set(STRICT_COMPILE_FLAGS)
endif ()

# Warnings for Debug mode
option(USE_STRICT_COMPILE_WARNINGS "Use strict compilation warnings in debug mode." ON)
# These compile flags should apply for GCC and Clang compilers
set(STRICT_COMPILE_FLAGS "-Wpedantic -Wall -Wno-c++98-compat -Wfloat-equal -Wextra -Wsign-promo -Wsign-compare -Wconversion -Wno-sign-conversion -Wno-unused-parameter")
if (USE_STRICT_COMPILE_WARNINGS)
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${STRICT_COMPILE_FLAGS}")
endif ()

# Find required packages
find_package(GLFW3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLM REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Freetype REQUIRED)
include_directories(${FREETYPE_INCLUDE_DIRS})

# Set default installation destination
if (NOT CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "../_install")
endif ()

# PPGSO library
add_library(libppgso STATIC
        src/lib/mesh.cpp
        src/lib/tiny_obj_loader.cpp
        src/lib/shader.cpp
        src/lib/texture.cpp
        src/lib/plane.cpp
        src/lib/texts.cpp
        src/lib/meshAnimate.cpp)
# Make sure GLM uses radians and static GLEW library
target_compile_definitions(libppgso PUBLIC -DGLM_FORCE_RADIANS -DGLEW_STATIC )
# Link to GLFW, GLEW and OpenGL
target_link_libraries(libppgso PUBLIC ${GLFW_LIBRARIES} ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES})
# Pass on include directories
target_include_directories(libppgso PUBLIC
        src/lib
        ${GLFW_INCLUDE_DIRS}
        ${GLEW_INCLUDE_DIRS}
        ${GLM_INCLUDE_DIRS}
        ${OPENGL_INCLUDE_DIRS}
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_CURRENT_BINARY_DIR})

#
# TARGETS
#

# gl_quickBall
set(GL_GAME_SRC
        src/main.cpp
        src/object.cpp
        src/scene.cpp
        src/camera.cpp
        src/asteroid.cpp
        src/player.cpp src/ground.cpp src/ground.h src/fence.cpp src/fence.h src/enemy.cpp src/enemy.h src/heart.cpp src/heart.h src/portal.cpp src/portal.h src/titlescreen.cpp src/titlescreen.h src/word.cpp src/word.h src/test1.cpp src/test1.h src/back.cpp src/back.h src/generator.cpp src/generator.h src/combined.cpp src/combined.h src/enemyAnimate.cpp src/enemyAnimate.h)
generate_shaders(GL_GAME_SHADERS
        src/glsl/object_frag.glsl
        src/glsl/object_frag_mono.glsl
        src/glsl/object_vert.glsl
        src/glsl/text_vert.glsl
        src/glsl/text_frag.glsl
        src/glsl/back_vert.glsl
        src/glsl/back_frag.glsl
        src/glsl/object_vert_anim.glsl)
add_executable(gl_quickball ${GL_GAME_SRC} ${GL_GAME_SHADERS})
target_link_libraries(gl_quickball libppgso ${FREETYPE_LIBRARIES})
install(TARGETS gl_quickball DESTINATION .)

# ADD YOUR PROJECT HERE
#set(MY_PROJECT_SRC src/my_project/my_project.cpp)
#generate_shaders(MY_PROJECT_SHADERS src/my_project/my_project_vert.glsl src/my_project/my_project_frag.glsl)
#add_executable(my_project ${MY_PROJECT_SRC} ${MY_PROJECT_SHADERS})
#target_link_libraries(my_project libppgso)
#install (TARGETS my_project DESTINATION .)

#
# INSTALLATION
#

install(DIRECTORY data/ DESTINATION .)
