/* texture.c
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

#include "texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

GLuint load_texture(const char *tex_path, int *w, int *h) {
  GLuint texture_id = 0;
  int num_channnel = 0;

  GLErrCall(glGenTextures(1, &texture_id));
  GLErrCall(glBindTexture(GL_TEXTURE_2D, texture_id));

  GLErrCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
  GLErrCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
  GLErrCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
  GLErrCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

  stbi_set_flip_vertically_on_load(1);
  unsigned char *img_data = stbi_load(tex_path, w, h, &num_channnel, 0);

  if (img_data) {
    GLErrCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, *w, *h, 0, GL_RGBA, GL_UNSIGNED_BYTE, img_data));
    GLErrCall(glGenerateMipmap(GL_TEXTURE_2D));
  } else {
    perror("ERR::TEXTURE::LOAD::FAILED");
  }

  stbi_image_free(img_data);

  return texture_id;
}

void bind_texture_to_object(Object *object, GLuint texture_id) {
  object->textures[object->num_textures++] = texture_id;
}
