/* object.h
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

#ifndef OBJECT_H
#define OBJECT_H

#include "gl.h"
#include <stdio.h>

typedef struct {
  GLuint *indices;
  float *vertexBufferData;
  GLuint *countOfEachAttr;
  size_t indexSize;
  size_t bufferSize;
  GLuint numberOfAttr;
  size_t vertexCount;
  GLuint textures[64];
  GLuint num_textures;
  GLuint vaoId;
  GLuint vboId;
  GLuint iboId;
} Object;

Object *create_object(void *vertexBufferData, size_t bufferSize,
                      GLuint *indices, size_t indexSize, size_t vertexCount,
                      GLuint *arrayOfAttr, GLuint numberOfAttr);

void destroy_object(Object **object);

#endif
