cmake_minimum_required(VERSION 3.5)

project(test_opengl_learn)

add_executable(test_shader test_shader.c $<TARGET_OBJECTS:opengl_learn_objects>)

target_include_directories(
  test_shader PUBLIC ${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/include/glad
                     ${CMAKE_SOURCE_DIR}/include ${glfw3_INCLUDE_DIRS})

set(MATH "")
include(CheckLibraryExists)
check_library_exists(m pow "" LIBM)
if(LIBM)
    list(APPEND MATH m)
endif()

target_link_libraries(test_shader utilities glfw ${MATH})

add_custom_command(
  TARGET test_shader
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/shaders/
          $<TARGET_FILE_DIR:test_shader>/shaders)

add_test(test_shader test_shader)
