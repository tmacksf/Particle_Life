cmake_minimum_required(VERSION 3.23)
project(Particle_Life)

set(CMAKE_CXX_STANDARD 17)

add_executable(Particle_Life main.cpp Particles.cpp Particle.cpp)

find_package(OpenGL REQUIRED)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(Dependencies/GLFW)
add_subdirectory(Dependencies/GLEW_cmake)

target_link_libraries(Particle_Life glfw ${OPENGL_gl_LIBRARY} libglew_static)