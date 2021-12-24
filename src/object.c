/* object.c
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

#include "object.h"
#include "common.h"

Object *create_object (void *vertexBufferData, size_t bufferSize,
                       GLuint *indicies, size_t indexSize, size_t vertexCount,
                       GLuint *arrayOfAttr, GLuint numberOfAttr) {
  if (!vertexBufferData || !arrayOfAttr) {
    printf("[ERROR] :: vertexBufferData or countOfEachAttr cannot be NULL %s:%d\n", __FILE__, __LINE__);
    return NULL;
  }

  Object *object = malloc(sizeof(Object));

  if (!object) {
    printf("[ERROR] :: Cannot allocate object %s:%d\n", __FILE__, __LINE__);
    return NULL;
  }

  object->num_textures = 0;
  object->indicies = indicies;
  object->vertexBufferData = vertexBufferData;
  object->countOfEachAttr = arrayOfAttr;
  object->bufferSize = bufferSize;
  object->numberOfAttr = numberOfAttr;

  if (indicies) {
    object->indexSize = indexSize;

    GLErrCall(glGenVertexArrays(1, &object->vaoId));
    GLErrCall(glGenBuffers(1, &object->vboId));
    GLErrCall(glGenBuffers(1, &object->iboId));

    GLErrCall(glBindVertexArray(object->vaoId));
    GLErrCall(glBindBuffer(GL_ARRAY_BUFFER, object->vboId));
    GLErrCall(glBufferData(GL_ARRAY_BUFFER, object->bufferSize, object->vertexBufferData, GL_STATIC_DRAW));

    GLErrCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object->iboId));
    GLErrCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, object->indexSize, object->indicies, GL_STATIC_DRAW));

    {
      GLuint size = 0, offset = 0;
      for (size_t i = 0; i < object->numberOfAttr; i++)
        size += object->countOfEachAttr[i];

      for (GLuint i = 0; i < object->numberOfAttr; i++) {
        GLErrCall(glVertexAttribPointer(i, object->countOfEachAttr[i], GL_FLOAT, GL_FALSE, size * sizeof(float), (void*)(uintptr_t)offset));
        GLErrCall(glEnableVertexAttribArray(i));
        offset += object->countOfEachAttr[i] * sizeof(float);
      }
    }

    GLErrCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

    GLErrCall(glBindVertexArray(0));
    GLErrCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
  } else {
    object->indexSize = 0;
    object->vertexCount = vertexCount;
    GLErrCall(glGenVertexArrays(1, &object->vaoId));
    GLErrCall(glGenBuffers(1, &object->vboId));

    GLErrCall(glBindVertexArray(object->vaoId));
    GLErrCall(glBindBuffer(GL_ARRAY_BUFFER, object->vboId));
    GLErrCall(glBufferData(GL_ARRAY_BUFFER, object->bufferSize, object->vertexBufferData, GL_STATIC_DRAW));

    {
      GLuint size = 0, offset = 0;
      for (size_t i = 0; i < object->numberOfAttr; i++)
        size += object->countOfEachAttr[i];

      for (GLuint i = 0; i < object->numberOfAttr; i++) {
        GLErrCall(glVertexAttribPointer(i, object->countOfEachAttr[i], GL_FLOAT, GL_FALSE, size * sizeof(float), (void*)&offset));
        GLErrCall(glEnableVertexAttribArray(i));
        offset += object->countOfEachAttr[i] * sizeof(float);
      }
    }

    GLErrCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

    GLErrCall(glBindVertexArray(0));
  }
  return object;
}

void destroy_object(Object **object) {
  if ((*object)->indicies) {
    GLErrCall(glDeleteVertexArrays(1, &(*object)->vaoId));
    GLErrCall(glDeleteBuffers(1, &(*object)->vboId));
    GLErrCall(glDeleteBuffers(1, &(*object)->iboId));
    GLErrCall(glDeleteTextures((*object)->num_textures, (*object)->textures));
  } else {
    GLErrCall(glDeleteVertexArrays(1, &(*object)->vaoId));
    GLErrCall(glDeleteBuffers(1, &(*object)->vboId));
  }
  free(*object);
  *object = NULL;
}
