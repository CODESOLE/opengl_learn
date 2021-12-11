/* common.c
 *
 * Copyright 2021 CODESOLE
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "common.h"

void GLClearError(void) {
  while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char *funcName, const char *file, int line) {
  GLenum error;
  while ((error = glGetError())) {
        switch (error) {
        case 0x0500:
            printf("[OpenGL Error] (GL_INVALID_ENUM)  FUNC_NAME: %s  FILE_NAME: %s  LINE: %d\n", funcName, file, line);
            break;
        case 0x0501:
            printf("[OpenGL Error] (GL_INVALID_VALUE)  FUNC_NAME: %s  FILE_NAME: %s  LINE: %d\n", funcName, file, line);
            break;
        case 0x0502:
            printf("[OpenGL Error] (GL_INVALID_OPERATION)  FUNC_NAME: %s  FILE_NAME: %s  LINE: %d\n", funcName, file, line);
            break;
        case 0x0503:
            printf("[OpenGL Error] (GL_STACK_OVERFLOW)  FUNC_NAME: %s  FILE_NAME: %s  LINE: %d\n", funcName, file, line);
            break;
        case 0x0504:
            printf("[OpenGL Error] (GL_STACK_UNDERDFLOW)  FUNC_NAME: %s  FILE_NAME: %s  LINE: %d\n", funcName, file, line);
            break;
        case 0x0505:
            printf("[OpenGL Error] (GL_OUT_OF_MEMORY)  FUNC_NAME: %s  FILE_NAME: %s  LINE: %d\n", funcName, file, line);
            break;
        case 0x0506:
            printf("[OpenGL Error] (GL_INVALID_FRAMEBUFFER_OPERATION)  FUNC_NAME: %s  FILE_NAME: %s  LINE: %d\n", funcName, file, line);
            break;
        default:
            printf("[OpenGL Error] (UNKNOWN_ERR_CODE => 0x0%x)  FUNC_NAME: %s  FILE_NAME: %s  LINE: %d\n", error, funcName, file, line);
            break;
        }
      return false;
    }
  return true;
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos) {}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {}

void error_callback(int error, const char *description) {
  UNUSED(error);
  fprintf(stderr, "Error: %s\n", description);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  UNUSED (window);
  GLErrCall (glViewport(0, 0, width, height));
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
  UNUSED(scancode); UNUSED(mods);
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
      glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void gl_clear_color(vec4 clearColor) {
  GLErrCall (glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]));
  GLErrCall (glClear(GL_COLOR_BUFFER_BIT));
}

GLFWwindow *init_glfw_glad(int width, int height, const char *windowName) {
  glfwSetErrorCallback(error_callback);

  if (!glfwInit())
      exit(EXIT_FAILURE);

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window = glfwCreateWindow(width, height, windowName, NULL, NULL);

  if (!window) {
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glfwSetKeyCallback(window, key_callback);
  glfwSetCursorPosCallback(window, mouse_callback);
  glfwSetScrollCallback(window, scroll_callback);

  glfwMakeContextCurrent(window);
  if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
    printf("Failed to initialize GLAD\n");
    exit(EXIT_FAILURE);
  }

  printf("Vendor:   %s\n", glGetString(GL_VENDOR));
  printf("Renderer: %s\n", glGetString(GL_RENDERER));
  printf("Version:  %s\n", glGetString(GL_VERSION));

  glfwSwapInterval(1);
  return window;
}

float calculate_ratio(GLFWwindow *window, int *width, int *height) {
  glfwGetFramebufferSize(window, width, height);
  return *width / (float) *height;
}

void glfw_routine(GLFWwindow *window) {
  glfwSwapBuffers(window);
  glfwPollEvents();
}

void destroy_terminate_glfw(GLFWwindow *window) {
  glfwDestroyWindow(window);
  glfwTerminate();
}
