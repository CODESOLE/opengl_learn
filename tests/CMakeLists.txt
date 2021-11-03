cmake_minimum_required(VERSION 3.2)

project(test_opengl_learn)

if (MSVC)

    add_compile_options(/W4 /WX)
    set( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup" )

    add_executable(test_shader test_shader.c $<TARGET_OBJECTS:opengl_learn_objects>)

    target_include_directories(test_shader PUBLIC 
        ${CMAKE_SOURCE_DIR}/src 
        ${CMAKE_SOURCE_DIR}/include/glad
        ${CMAKE_SOURCE_DIR}/include 
      )

    target_link_libraries(test_shader ${CMAKE_SOURCE_DIR}/deps/windows/MSVC/glfw3dll.lib utilities)

    add_custom_command(TARGET test_shader POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/shaders/ $<TARGET_FILE_DIR:test_shader>/shaders)

    add_custom_command(TARGET test_shader POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E copy
                       ${CMAKE_SOURCE_DIR}/deps/windows/MSVC/glfw3.dll $<TARGET_FILE_DIR:test_shader>)

elseif(UNIX AND NOT APPLE)

    find_package(glfw3 3.3 REQUIRED)
    find_package(OpenGL REQUIRED)

    add_executable(test_shader test_shader.c $<TARGET_OBJECTS:opengl_learn_objects>)

    target_include_directories(test_shader PUBLIC 
        ${CMAKE_SOURCE_DIR}/src 
        ${CMAKE_SOURCE_DIR}/include/glad
        ${CMAKE_SOURCE_DIR}/include 
      )

    target_compile_options(test_shader PRIVATE -Wall -Wextra -Werror -pedantic -pedantic-errors)
    target_include_directories(test_shader PUBLIC src include/glad )
    target_link_libraries(test_shader glfw OpenGL::GL dl utilities)

    add_custom_command(TARGET test_shader POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/shaders/ $<TARGET_FILE_DIR:test_shader>/shaders)

    find_library(RT_LIBRARY rt)
    mark_as_advanced(RT_LIBRARY)

    find_library(MATH_LIBRARY m)
    mark_as_advanced(MATH_LIBRARY)

    if (MATH_LIBRARY)
      target_link_libraries(test_shader ${MATH_LIBRARY})
    endif()

    if (RT_LIBRARY)
      target_link_libraries(test_shader "${RT_LIBRARY}")
    endif()

elseif(CMAKE_C_SIMULATE_ID STREQUAL "MSVC")

    add_executable(test_shader test_shader.c $<TARGET_OBJECTS:opengl_learn_objects>)

    target_include_directories(test_shader PUBLIC 
        ${CMAKE_SOURCE_DIR}/src 
        ${CMAKE_SOURCE_DIR}/include/glad
        ${CMAKE_SOURCE_DIR}/include 
      )

    target_compile_options(test_shader PRIVATE -Wall -Wextra -Werror -pedantic -pedantic-errors)

    target_link_libraries(test_shader ${CMAKE_SOURCE_DIR}/deps/windows/MSVC/glfw3dll.lib utilities)

    add_custom_command(TARGET test_shader POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E copy
                       ${CMAKE_SOURCE_DIR}/deps/windows/MSVC/glfw3.dll $<TARGET_FILE_DIR:test_shader>)

    add_custom_command(TARGET test_shader POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/shaders/ $<TARGET_FILE_DIR:test_shader>/shaders)

else()

    add_executable(test_shader test_shader.c $<TARGET_OBJECTS:opengl_learn_objects>)

    target_include_directories(test_shader PUBLIC 
        ${CMAKE_SOURCE_DIR}/src 
        ${CMAKE_SOURCE_DIR}/include/glad
        ${CMAKE_SOURCE_DIR}/include 
      )

    target_compile_options(test_shader PRIVATE -Wall -Wextra -Werror -pedantic -pedantic-errors)

    target_link_libraries(test_shader ${CMAKE_SOURCE_DIR}/deps/windows/MinGW-W64/libglfw3.a utilities)

    add_custom_command(TARGET test_shader POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/shaders/ $<TARGET_FILE_DIR:test_shader>/shaders)

endif()

add_test(test_shader test_shader)
