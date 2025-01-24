
cmake_minimum_required(VERSION 3.29)
project(openGL_clion)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(Libraries/include/glad)
add_subdirectory(Libraries/include/GLFW)
add_subdirectory(Libraries/include/glm)
add_subdirectory(imGui)
add_subdirectory(sphere)
add_subdirectory(glfw)

file(GLOB_RECURSE SOURCE
        ./source/*.c ./source/*.h
        ./source/*.cpp ./source/*.hpp
        ./imGui/*.cpp ./imGui/.*h
        ./sphere/*.cpp ./sphere*.h)

link_directories(Libraries/lib)
include_directories(openGL_clion PRIVATE Libraries/include)
#include_directories(openGL_clion PRIVATE imGui)

add_executable(openGL_clion ${SOURCE})
set_target_properties(openGL_clion PROPERTIES LINKER_LANGUAGE CXX LINK_FLAGS "-Wl,--subsystem,console")

target_link_libraries(openGL_clion opengl32 gdi32 glfw)
