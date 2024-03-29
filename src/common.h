/* common.h general common stuff
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

#ifndef COMMON_H
#define COMMON_H

#define GLFW_INCLUDE_NONE
#include "debugbreak.h"
#include "gl.h"
#include "linmath.h"
#include "object.h"
#include <GLFW/glfw3.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define ASSERT(x)                                                              \
  if (!(x))                                                                    \
    debug_break();

#ifndef NDEBUG
#define GLErrCall(x)                                                           \
  GLClearError();                                                              \
  x;                                                                           \
  ASSERT(GLLogCall(#x, __FILE__, __LINE__))
#else
#define GLErrCall(x) x
#endif

#define UNUSED(expr)                                                           \
  do {                                                                         \
    (void)(expr);                                                              \
  } while (0)

#define RED_COLOR                                                              \
  (vec4) { 1.0f, 0.0f, 0.0f, 1.0f }
#define BLACK_COLOR                                                            \
  (vec4) { 0.0f, 0.0f, 0.0f, 1.0f }

void GLClearError(void);

_Bool GLLogCall(const char *funcName, const char *file, int line);

void mouse_callback(GLFWwindow *window, double xpos, double ypos);

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

void error_callback(int error, const char *description);

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void key_callback(GLFWwindow *window, int key, int scancode, int action,
                  int mods);

void gl_clear_color(vec4 clearColor);

GLFWwindow *init_glfw_glad(int width, int height, const char *windowName);

float calculate_ratio(GLFWwindow *window, int *width, int *height);

void glfw_routine(GLFWwindow *window);

void destroy_terminate_glfw(GLFWwindow *window);

/*
 * Copy string src to buffer dst of size dsize.  At most dsize-1
 * chars will be copied.  Always NUL terminates (unless dsize == 0).
 * Returns strlen(src); if retval >= dsize, truncation occurred.
 */
size_t xstrlcpy(char *dst, const char *src, size_t siz);
/*
 * Appends src to string dst of size dsize (unlike strncat, dsize is the
 * full size of dst, not space left).  At most dsize-1 characters
 * will be copied.  Always NUL terminates (unless dsize <= strlen(dst)).
 * Returns strlen(src) + MIN(dsize, strlen(initial dst)).
 * If retval >= dsize, truncation occurred.
 */
size_t xstrlcat(char *dst, const char *src, size_t siz);
size_t xstrnlen(const char *s, size_t n);
char *xstrndup(const char *s, size_t n);

#endif
