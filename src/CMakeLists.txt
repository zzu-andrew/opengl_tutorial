cmake_minimum_required(VERSION 3.2)
project(opengl)

set(CMAKE_CXX_STANDARD 14)

message("top: CMAKE_CURRENT_SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR}")

set(CMAKE_C_FLAGS_PROFILE "-p -g -O2 -DSHADER_DIR=\"${CMAKE_CURRENT_SOURCE_DIR}/shader_src\"" CACHE STRING "")
set(CMAKE_CXX_FLAGS_PROFILE "-p -g -O2 -DSHADER_DIR=\"${CMAKE_CURRENT_SOURCE_DIR}/shader_src\"" CACHE STRING "")

add_executable(opengl_test
        opengl_demo/opengl_test.cpp
        glad/glad.c)
target_link_libraries(opengl_test
        PUBLIC GL
        PUBLIC glut
        PUBLIC dl
        PUBLIC Xrandr
        PUBLIC Xi
        PUBLIC GLEW
        PUBLIC glfw3
        PUBLIC pthread)
target_include_directories(opengl_test
        PUBLIC ./../inc)

add_executable(opengl_window_demo
        opengl_window/opengl_window_demo.cpp
        glad/glad.c)
target_link_libraries(opengl_window_demo
        PUBLIC GL
        PUBLIC glut
        PUBLIC dl
        PUBLIC Xrandr
        PUBLIC Xi
        PUBLIC GLEW
        PUBLIC glfw3
        PUBLIC pthread)
target_include_directories(opengl_window_demo
    PUBLIC ./../inc)

add_executable(triangle_demo
        opengl_triangle/triangle_demo.cpp
        glad/glad.c)
target_link_libraries(triangle_demo
        PUBLIC GL
        PUBLIC glut
        PUBLIC dl
        PUBLIC Xrandr
        PUBLIC Xi
        PUBLIC GLEW
        PUBLIC glfw3
        PUBLIC pthread)
target_include_directories(triangle_demo
        PUBLIC ./../inc)
#
add_executable(rectangle_demo
        opengl_triangle/rectangle_demo.cpp
        glad/glad.c)
target_link_libraries(rectangle_demo
        PUBLIC GL
        PUBLIC glut
        PUBLIC dl
        PUBLIC Xrandr
        PUBLIC Xi
        PUBLIC GLEW
        PUBLIC glfw3
        PUBLIC pthread)
target_include_directories(rectangle_demo
        PUBLIC ./../inc)

# 多个三角形
add_executable(multi_triangle
        opengl_triangle/multi_triangle.cpp
        glad/glad.c)
target_link_libraries(multi_triangle
        PUBLIC GL
        PUBLIC glut
        PUBLIC dl
        PUBLIC Xrandr
        PUBLIC Xi
        PUBLIC GLEW
        PUBLIC glfw3
        PUBLIC pthread)
target_include_directories(multi_triangle
        PUBLIC ./../inc)
# 使用多vertex的三角形
add_executable(multi_vertex_triangle
        opengl_triangle/multi_vertex_triangle.cpp
        glad/glad.c)
target_link_libraries(multi_vertex_triangle
        PUBLIC GL
        PUBLIC glut
        PUBLIC dl
        PUBLIC Xrandr
        PUBLIC Xi
        PUBLIC GLEW
        PUBLIC glfw3
        PUBLIC pthread)
target_include_directories(multi_vertex_triangle
        PUBLIC ./../inc)

# 使用多vertex的三角形
add_executable(multi_color_triangle
        opengl_triangle/multi_color_triangle.cpp
        glad/glad.c)
target_link_libraries(multi_color_triangle
        PUBLIC GL
        PUBLIC glut
        PUBLIC dl
        PUBLIC Xrandr
        PUBLIC Xi
        PUBLIC GLEW
        PUBLIC glfw3
        PUBLIC pthread)
target_include_directories(multi_color_triangle
        PUBLIC ./../inc)

# 使用多vertex的三角形
add_executable(dynamic_color_triangle
        opengl_triangle/dynamic_color_triangle.cpp
        glad/glad.c)
target_link_libraries(dynamic_color_triangle
        PUBLIC GL
        PUBLIC glut
        PUBLIC dl
        PUBLIC Xrandr
        PUBLIC Xi
        PUBLIC GLEW
        PUBLIC glfw3
        PUBLIC m
        PUBLIC pthread)
target_include_directories(dynamic_color_triangle
        PUBLIC ./../inc)

# 颜色渐变的三角形
add_executable(gradual_color_triangle
        opengl_triangle/gradual_color_triangle.cpp
        glad/glad.c)
target_link_libraries(gradual_color_triangle
        PUBLIC GL
        PUBLIC glut
        PUBLIC dl
        PUBLIC Xrandr
        PUBLIC Xi
        PUBLIC GLEW
        PUBLIC glfw3
        PUBLIC pthread)
target_include_directories(gradual_color_triangle
        PUBLIC ./../inc)

# 颜色渐变的三角形
add_executable(shader_triangle_demo
        shader_triangle/shader_triangle_demo.cpp
        glad/glad.c)
target_link_libraries(shader_triangle_demo
        PUBLIC GL
        PUBLIC glut
        PUBLIC dl
        PUBLIC Xrandr
        PUBLIC Xi
        PUBLIC GLEW
        PUBLIC glfw3
        PUBLIC pthread)
target_include_directories(shader_triangle_demo
        PUBLIC ./../inc)

# 通过改变vs文件实现三角形的反转,改变y 上下反转，改变x左右反转
add_executable(shader_triangle_exercise1
        shader_triangle/shader_triangle_exercise1.cpp
        glad/glad.c)
target_link_libraries(shader_triangle_exercise1
        PUBLIC GL
        PUBLIC glut
        PUBLIC dl
        PUBLIC Xrandr
        PUBLIC Xi
        PUBLIC GLEW
        PUBLIC glfw3
        PUBLIC pthread)
target_include_directories(shader_triangle_exercise1
        PUBLIC ./../inc)

# 通过uniform移动图形
add_executable(shader_triangle_exercise2
        shader_triangle/shader_triangle_exercise2.cpp
        glad/glad.c)
target_link_libraries(shader_triangle_exercise2
        PUBLIC GL
        PUBLIC glut
        PUBLIC dl
        PUBLIC Xrandr
        PUBLIC Xi
        PUBLIC GLEW
        PUBLIC glfw3
        PUBLIC pthread)
target_include_directories(shader_triangle_exercise2
        PUBLIC ./../inc)

# 按照三角形的标点绘制颜色
add_executable(shader_triangle_exercise3
        shader_triangle/shader_triangle_exercise3.cpp
        glad/glad.c)
target_link_libraries(shader_triangle_exercise3
        PUBLIC GL
        PUBLIC glut
        PUBLIC dl
        PUBLIC Xrandr
        PUBLIC Xi
        PUBLIC GLEW
        PUBLIC glfw3
        PUBLIC pthread)
target_include_directories(shader_triangle_exercise3
        PUBLIC ./../inc)

# 按照三角形的标点绘制颜色
add_executable(texture_demo
        textures_demo/texture_demo.cpp
        glad/glad.c
        stb_image/stb_image.cpp)
target_link_libraries(texture_demo
        PUBLIC GL
        PUBLIC glut
        PUBLIC dl
        PUBLIC Xrandr
        PUBLIC Xi
        PUBLIC GLEW
        PUBLIC glfw3
        PUBLIC pthread)
target_include_directories(texture_demo
        PUBLIC ./../inc)

# 多个纹理 混合使用
add_executable(texture_unit
        textures_demo/texture_unit.cpp
        glad/glad.c
        stb_image/stb_image.cpp)
target_link_libraries(texture_unit
        PUBLIC GL
        PUBLIC glut
        PUBLIC dl
        PUBLIC Xrandr
        PUBLIC Xi
        PUBLIC GLEW
        PUBLIC glfw3
        PUBLIC pthread)
target_include_directories(texture_unit
        PUBLIC ./../inc)

# 多纹理的使用 x轴镜像
add_executable(texture_exercise1
        textures_demo/texture_exercise1.cpp
        glad/glad.c
        stb_image/stb_image.cpp)
target_link_libraries(texture_exercise1
        PUBLIC GL
        PUBLIC glut
        PUBLIC dl
        PUBLIC Xrandr
        PUBLIC Xi
        PUBLIC GLEW
        PUBLIC glfw3
        PUBLIC pthread)
target_include_directories(texture_exercise1
        PUBLIC ./../inc)

# 多纹理的使用
add_executable(texture_exercise2
        textures_demo/texture_exercise2.cpp
        glad/glad.c
        stb_image/stb_image.cpp)
target_link_libraries(texture_exercise2
        PUBLIC GL
        PUBLIC glut
        PUBLIC dl
        PUBLIC Xrandr
        PUBLIC Xi
        PUBLIC GLEW
        PUBLIC glfw3
        PUBLIC pthread)
target_include_directories(texture_exercise2
        PUBLIC ./../inc)