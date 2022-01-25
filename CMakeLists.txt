cmake_minimum_required(VERSION 3.2)

project(opengl_learn)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(utilities)

add_library(opengl_learn_objects OBJECT 
  ${CMAKE_SOURCE_DIR}/src/common.c
  ${CMAKE_SOURCE_DIR}/src/draw.c
  ${CMAKE_SOURCE_DIR}/src/object.c
  ${CMAKE_SOURCE_DIR}/src/parse_shader.c
  ${CMAKE_SOURCE_DIR}/src/shader_program.c
  ${CMAKE_SOURCE_DIR}/src/texture.c
  ${CMAKE_SOURCE_DIR}/include/glad/glad.c
  )

if (MSVC)

  message(STATUS "NATIVE MSVC TOOL-CHAIN")
  add_compile_options(/W4 /WX)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
  set( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup" )

  target_include_directories(opengl_learn_objects PUBLIC src include include/glad include)
  target_link_libraries(opengl_learn_objects ${CMAKE_SOURCE_DIR}/deps/windows/MSVC/glfw3dll.lib utilities)

  add_executable(opengl_learn WIN32 src/main.c $<TARGET_OBJECTS:opengl_learn_objects>)

  target_include_directories(opengl_learn PUBLIC src include include/glad include)
  target_link_libraries(opengl_learn ${CMAKE_SOURCE_DIR}/deps/windows/MSVC/glfw3dll.lib utilities)

  add_custom_command(TARGET opengl_learn POST_BUILD
                     COMMAND ${CMAKE_COMMAND} -E copy_directory
                     ${CMAKE_SOURCE_DIR}/shaders/ $<TARGET_FILE_DIR:opengl_learn>/shaders)

  add_custom_command(TARGET opengl_learn POST_BUILD
                     COMMAND ${CMAKE_COMMAND} -E copy
                     ${CMAKE_SOURCE_DIR}/deps/windows/MSVC/glfw3.dll $<TARGET_FILE_DIR:opengl_learn>)

elseif(UNIX AND NOT APPLE)

  if(POLICY CMP0072)
    cmake_policy(SET CMP0072 NEW)
  endif()

  message(STATUS "NATIVE LINUX OR BSD")
  add_compile_options(-Wall -Wextra -Werror -pedantic -pedantic-errors)
  find_package(glfw3 3.3 REQUIRED)
  find_package(OpenGL REQUIRED)
  target_include_directories(opengl_learn_objects PUBLIC src include include/glad )
  target_link_libraries(opengl_learn_objects glfw dl OpenGL::GL utilities)

  add_executable(opengl_learn src/main.c $<TARGET_OBJECTS:opengl_learn_objects>)
  target_include_directories(opengl_learn PUBLIC src include include/glad )
  target_link_libraries(opengl_learn glfw OpenGL::GL dl utilities)

  add_custom_command(TARGET opengl_learn POST_BUILD
                     COMMAND ${CMAKE_COMMAND} -E copy_directory
                     ${CMAKE_SOURCE_DIR}/shaders/ $<TARGET_FILE_DIR:opengl_learn>/shaders)

  find_library(RT_LIBRARY rt)
  mark_as_advanced(RT_LIBRARY)

  find_library(MATH_LIBRARY m)
  mark_as_advanced(MATH_LIBRARY)

  if (MATH_LIBRARY)
    target_link_libraries(opengl_learn ${MATH_LIBRARY})
  endif()

  if (RT_LIBRARY)
    target_link_libraries(opengl_learn "${RT_LIBRARY}")
  endif()

elseif(CMAKE_C_SIMULATE_ID STREQUAL "MSVC")

  message(STATUS "C_SIMULATE_ID == MSVC (Probably Clang on WINDOWS)")
  # Tell Clang using MS CRT to use main instead of WinMain
  set( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,/entry:mainCRTStartup" )
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)

  target_include_directories(opengl_learn_objects PUBLIC src include/glad include)
  target_link_libraries(opengl_learn_objects ${CMAKE_SOURCE_DIR}/deps/windows/MSVC/glfw3dll.lib utilities)

  add_executable(opengl_learn WIN32 src/main.c $<TARGET_OBJECTS:opengl_learn_objects>)

  target_include_directories(opengl_learn PUBLIC src include/glad include)
  target_link_libraries(opengl_learn ${CMAKE_SOURCE_DIR}/deps/windows/MSVC/glfw3dll.lib utilities)

  add_custom_command(TARGET opengl_learn POST_BUILD
                     COMMAND ${CMAKE_COMMAND} -E copy
                     ${CMAKE_SOURCE_DIR}/deps/windows/MSVC/glfw3.dll $<TARGET_FILE_DIR:opengl_learn>)

  add_custom_command(TARGET opengl_learn POST_BUILD
                     COMMAND ${CMAKE_COMMAND} -E copy_directory
                     ${CMAKE_SOURCE_DIR}/shaders/ $<TARGET_FILE_DIR:opengl_learn>/shaders)

else()

  message(STATUS "MINGW-W64 BUILD TOOL-CHAIN")
  add_compile_options(-Wall -Wextra -Werror -pedantic -pedantic-errors)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
  target_include_directories(opengl_learn_objects PUBLIC src include/glad include)
  target_link_libraries(opengl_learn_objects ${CMAKE_SOURCE_DIR}/deps/windows/MinGW-W64/libglfw3.a utilities)

  add_executable(opengl_learn WIN32 src/main.c $<TARGET_OBJECTS:opengl_learn_objects>)
  
  target_include_directories(opengl_learn PUBLIC src include/glad include)
  target_link_libraries(opengl_learn ${CMAKE_SOURCE_DIR}/deps/windows/MinGW-W64/libglfw3.a utilities)

  add_custom_command(TARGET opengl_learn POST_BUILD
                     COMMAND ${CMAKE_COMMAND} -E copy_directory
                     ${CMAKE_SOURCE_DIR}/shaders/ $<TARGET_FILE_DIR:opengl_learn>/shaders)

endif()

enable_testing()

add_subdirectory(tests)
