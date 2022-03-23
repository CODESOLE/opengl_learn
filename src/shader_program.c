/* shader_program.c
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

#include "shader_program.h"
#include "shader_program_private.h"

GLint check_and_get_uniform(ShaderProgram *shaderProgram,
                            const char *uniform_name) {
  void *u_name = NULL;
  if ((u_name = map_find_by_string_key(shaderProgram->uniformCache,
                                       (void *)uniform_name)) != NULL)
    return *(int *)u_name;
  else {
    GLint *location = malloc(sizeof(GLint));
    GLErrCall(*location = glGetUniformLocation(shaderProgram->shaderProgramID,
                                               uniform_name));
    if (*location == -1) {
      printf("WARNING: Uniform %s doesn't exist in shader!\n", uniform_name);
      free(location);
      return -1;
    }

    map_push_back_with_string_key(shaderProgram->uniformCache, uniform_name,
                                  (void *)location);

    return *location;
  }
}

ShaderProgram *create_shader_program(const char *shaderFileName) {
  ShaderProgram *shaderProgram = calloc(1, sizeof(ShaderProgram));
  shaderProgram->uniformCache = init_map(MAP_HEAP);
  VertexFragmentShader *vertFragSource = parse_shader(shaderFileName);

  if (vertFragSource->fragmentShader == NULL ||
      vertFragSource->vertexShader == NULL) {
    perror("ERR::Cannot parse shader source file");
    exit(EXIT_FAILURE);
  }

  GLErrCall(GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER));
  GLErrCall(glShaderSource(vertexShader, 1,
                           (const char **)&vertFragSource->vertexShader, NULL));
  GLErrCall(glCompileShader(vertexShader));

  int success = 0;
  char infoLog[512] = {0};
  GLErrCall(glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success));
  if (!success) {
    GLErrCall(glGetShaderInfoLog(vertexShader, 512, NULL, infoLog));
    fprintf(stderr, "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s\n", infoLog);
  }

  GLErrCall(GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER));
  GLErrCall(glShaderSource(
      fragmentShader, 1, (const char **)&vertFragSource->fragmentShader, NULL));
  GLErrCall(glCompileShader(fragmentShader));

  GLErrCall(glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success));
  if (!success) {
    GLErrCall(glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog));
    fprintf(stderr, "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s\n",
            infoLog);
  }

  GLErrCall(shaderProgram->shaderProgramID = glCreateProgram());
  GLErrCall(glAttachShader(shaderProgram->shaderProgramID, vertexShader));
  GLErrCall(glAttachShader(shaderProgram->shaderProgramID, fragmentShader));
  GLErrCall(glLinkProgram(shaderProgram->shaderProgramID));

  GLErrCall(
      glGetProgramiv(shaderProgram->shaderProgramID, GL_LINK_STATUS, &success));
  if (!success) {
    GLErrCall(glGetProgramInfoLog(shaderProgram->shaderProgramID, 512, NULL,
                                  infoLog));
    fprintf(stderr, "ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s\n", infoLog);
  }

  GLErrCall(glDeleteShader(vertexShader));
  GLErrCall(glDeleteShader(fragmentShader));

  free(vertFragSource->vertexShader);
  free(vertFragSource->fragmentShader);
  free(vertFragSource);

  return shaderProgram;
}

ShaderProgram *create_shader_program_vs_fs(const char *vertexSource,
                                           const char *fragmentSource) {
  ShaderProgram *shaderProgram = calloc(1, sizeof(ShaderProgram));
  shaderProgram->uniformCache = init_map(MAP_HEAP);
  VertexFragmentShader *vertFragSource =
      parse_shader_vs_fs(vertexSource, fragmentSource);

  if (vertFragSource->fragmentShader == NULL ||
      vertFragSource->vertexShader == NULL) {
    perror("ERR::Cannot parse shader source file");
    exit(EXIT_FAILURE);
  }

  GLErrCall(GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER));
  GLErrCall(glShaderSource(vertexShader, 1,
                           (const char **)&vertFragSource->vertexShader, NULL));
  GLErrCall(glCompileShader(vertexShader));

  int success = 0;
  char infoLog[512] = {0};
  GLErrCall(glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success));
  if (!success) {
    GLErrCall(glGetShaderInfoLog(vertexShader, 512, NULL, infoLog));
    fprintf(stderr, "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s\n", infoLog);
  }

  GLErrCall(GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER));
  GLErrCall(glShaderSource(
      fragmentShader, 1, (const char **)&vertFragSource->fragmentShader, NULL));
  GLErrCall(glCompileShader(fragmentShader));

  GLErrCall(glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success));
  if (!success) {
    GLErrCall(glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog));
    fprintf(stderr, "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s\n",
            infoLog);
  }

  GLErrCall(shaderProgram->shaderProgramID = glCreateProgram());
  GLErrCall(glAttachShader(shaderProgram->shaderProgramID, vertexShader));
  GLErrCall(glAttachShader(shaderProgram->shaderProgramID, fragmentShader));
  GLErrCall(glLinkProgram(shaderProgram->shaderProgramID));

  GLErrCall(
      glGetProgramiv(shaderProgram->shaderProgramID, GL_LINK_STATUS, &success));
  if (!success) {
    GLErrCall(glGetProgramInfoLog(shaderProgram->shaderProgramID, 512, NULL,
                                  infoLog));
    fprintf(stderr, "ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s\n", infoLog);
  }

  GLErrCall(glDeleteShader(vertexShader));
  GLErrCall(glDeleteShader(fragmentShader));

  free(vertFragSource->vertexShader);
  free(vertFragSource->fragmentShader);
  free(vertFragSource);

  return shaderProgram;
}

void use_shader(ShaderProgram *shaderProgram) {
  GLErrCall(glUseProgram(shaderProgram->shaderProgramID));
}

void unuse_shader(void) { GLErrCall(glUseProgram(0)); }

void destroy_shader(ShaderProgram **shaderProgram) {
  GLErrCall(glDeleteProgram((*shaderProgram)->shaderProgramID));
  map_destroy((*shaderProgram)->uniformCache);
  free(*shaderProgram);
  *shaderProgram = NULL;
}

void set_shader_uniform(ShaderProgram *shaderProgram, const char *uniformName,
                        const void *value, ShaderUniformDataType uniformType) {
  set_shader_uniform_v(shaderProgram, uniformName, value, uniformType, 1);
}

void set_shader_uniform_v(ShaderProgram *shaderProgram, const char *uniformName,
                          const void *value, ShaderUniformDataType uniformType,
                          GLuint count) {
  use_shader(shaderProgram);
  GLint loc = check_and_get_uniform(shaderProgram, uniformName);
  if (loc == -1)
    return;

  switch (uniformType) {
  case UNIFORM_FLOAT:
    glUniform1fv(loc, count, (float *)value);
    break;
  case UNIFORM_VEC2:
    glUniform2fv(loc, count, (float *)value);
    break;
  case UNIFORM_VEC3:
    glUniform3fv(loc, count, (float *)value);
    break;
  case UNIFORM_VEC4:
    glUniform4fv(loc, count, (float *)value);
    break;
  case UNIFORM_INT:
    glUniform1iv(loc, count, (int *)value);
    break;
  case UNIFORM_INT_VEC2:
    glUniform2iv(loc, count, (int *)value);
    break;
  case UNIFORM_INT_VEC3:
    glUniform3iv(loc, count, (int *)value);
    break;
  case UNIFORM_INT_VEC4:
    glUniform4iv(loc, count, (int *)value);
    break;
  case UNIFORM_SAMPLER2D:
    glUniform1iv(loc, count, (int *)value);
    break;
  default:
    fprintf(stderr,
            "SHADER: [ID %u] Failed to set uniform, data type not recognized\n",
            shaderProgram->shaderProgramID);
  }
}
