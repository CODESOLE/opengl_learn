
/* parse_shader.h
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



#ifndef PARSE_SHADER
#define PARSE_SHADER

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_READ_CHAR 999

typedef struct {
  char *vertexShader;
  char *fragmentShader;
} VertexFragmentShader;


VertexFragmentShader *parse_shader(const char *shader_file);

VertexFragmentShader *parse_shader_vs_fs(const char *vertexS, const char *fragmentS);

#endif
