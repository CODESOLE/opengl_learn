cmake_minimum_required(VERSION 3.5)

project(opengl_learn C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_subdirectory(utilities)

find_package(glfw3 3.3 REQUIRED)

set(MATH "")
include(CheckLibraryExists)
check_library_exists(m pow "" LIBM)
if(LIBM)
  list(APPEND MATH m)
endif()

if(MSVC)
  add_compile_options(/W4 /WX)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
else()
  add_compile_options(-Wall -Wextra -Werror -Wpedantic -pedantic
                      -pedantic-errors)
endif()

add_library(
  opengl_learn_objects OBJECT
  ${CMAKE_SOURCE_DIR}/src/common.c
  ${CMAKE_SOURCE_DIR}/src/draw.c
  ${CMAKE_SOURCE_DIR}/src/object.c
  ${CMAKE_SOURCE_DIR}/src/parse_shader.c
  ${CMAKE_SOURCE_DIR}/src/shader_program.c
  ${CMAKE_SOURCE_DIR}/src/texture.c
  ${CMAKE_SOURCE_DIR}/include/glad/glad.c)

target_include_directories(opengl_learn_objects PUBLIC src include/glad include
                                                       utilities)
target_link_libraries(opengl_learn_objects glfw ${MATH})

add_executable(opengl_learn src/main.c $<TARGET_OBJECTS:opengl_learn_objects>)
target_include_directories(opengl_learn PUBLIC src include/glad include
                                               utilities)
target_link_libraries(opengl_learn glfw ${MATH})

add_custom_command(
  TARGET opengl_learn
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/shaders/
          $<TARGET_FILE_DIR:opengl_learn>/shaders)

enable_testing()

add_subdirectory(tests)
