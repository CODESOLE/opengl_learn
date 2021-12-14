/* draw.c
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

#include "draw.h"

void draw (Object *object, ShaderProgram *shaderProgram) {
  use_shader(shaderProgram);
  GLErrCall (glBindVertexArray(object->vaoId));
  if (object->indicies) {
    GLErrCall (glDrawElements(GL_TRIANGLES, (GLsizei)object->indexSize, GL_UNSIGNED_INT, 0));
  } else {
    GLErrCall (glDrawArrays(GL_TRIANGLES, 0, (GLsizei)object->vertexCount));
  }
  glBindVertexArray(0);
}
