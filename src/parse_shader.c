/* parse_shader.c
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

#include "parse_shader.h"

VertexFragmentShader *parse_shader_vs_fs(const char *vertexS, const char *fragmentS) {
  if ((vertexS == NULL) || (fragmentS == NULL)) {
    puts("vertex shader source or fragment shader source is cannot be NULL");
    return NULL;
  }
  if (strlen(vertexS) < 4 || strlen(fragmentS) < 4) {
    puts("Invalid file!");
    return NULL;
  }
  if (strncmp(vertexS + strlen(vertexS) - 3, ".vs", 3) != 0) {
    puts("File should be ended with .vs!");
    return NULL;
  }

  if (strncmp(fragmentS + strlen(fragmentS) - 3, ".fs", 3) != 0) {
    puts("File should be ended with .fs!");
    return NULL;
  }

  FILE *vertexFile = fopen(vertexS, "r");
  if (vertexFile == NULL) {
    fprintf(stderr, "Error opening file: %s\n", vertexS);
    return NULL;
  }

  char line[MAX_READ_CHAR] = { 0 };
  VertexFragmentShader *parsed_data = calloc(1, sizeof (VertexFragmentShader));
  parsed_data->vertexShader = malloc(1);
  strcpy(parsed_data->vertexShader, "");
  parsed_data->fragmentShader = malloc(1);
  strcpy(parsed_data->fragmentShader, "");

  while (fgets(line, MAX_READ_CHAR, vertexFile) != NULL) {
    parsed_data->vertexShader = realloc(parsed_data->vertexShader,
                                        strlen(parsed_data->vertexShader) +
                                        strlen(line) + 1);

    strncat(parsed_data->vertexShader, line, strlen(parsed_data->vertexShader) + strlen(line) + 1);
  }
  fclose(vertexFile);

  FILE *fragmentFile = fopen(fragmentS, "r");
  if (fragmentFile == NULL) {
    fprintf(stderr, "Error opening file: %s\n", fragmentS);
    return NULL;
  }

  while (fgets(line, MAX_READ_CHAR, fragmentFile) != NULL) {
    parsed_data->fragmentShader = realloc(parsed_data->fragmentShader,
                                          strlen(parsed_data->fragmentShader) +
                                          strlen(line) + 1);

    strncat(parsed_data->fragmentShader, line, strlen(parsed_data->fragmentShader) + strlen(line) + 1);
  }
  fclose(fragmentFile);

  return parsed_data;
}

VertexFragmentShader *parse_shader(const char *shader_file) {
  if (strlen(shader_file) < 8) {
    puts("Invalid file!");
    return NULL;
  }
  if (strncmp(shader_file + strlen(shader_file) - 7, ".shader", 7) != 0) {
    puts("File should be ended with .shader!");
    return NULL;
  }

  FILE *file = fopen(shader_file, "r");
  if (file == NULL) {
    fprintf(stderr, "Error opening file: %s\n", shader_file);
    return NULL;
  }

  char line[MAX_READ_CHAR] = { 0 };
  VertexFragmentShader *parsed_data = calloc(1, sizeof (VertexFragmentShader));
  parsed_data->vertexShader = malloc(1);
  strcpy(parsed_data->vertexShader, "");
  parsed_data->fragmentShader = malloc(1);
  strcpy(parsed_data->fragmentShader, "");
  unsigned vertexFound = 0, fragmentFound = 0;

  while (fgets(line, MAX_READ_CHAR, file) != NULL) {
    if (strncmp(line, "#vertex", 7) == 0) {
vertex:
      vertexFound = 1;
      while (fgets(line, MAX_READ_CHAR, file) != NULL) {
        if (strncmp(line, "#fragment", 9) == 0)
            goto fragment;

        parsed_data->vertexShader = realloc(parsed_data->vertexShader,
                                            strlen(parsed_data->vertexShader) +
                                            strlen(line) + 1);

        strncat(parsed_data->vertexShader, line, strlen(parsed_data->vertexShader) + strlen(line) + 1);
      }

    } else if (strncmp(line, "#fargment", 9) == 0) {
fragment:
      fragmentFound = 1;
      while (fgets(line, MAX_READ_CHAR, file) != NULL) {
        if (strncmp(line, "#vertex", 7) == 0)
            goto vertex;

        parsed_data->fragmentShader = realloc(parsed_data->fragmentShader,
                                              strlen(parsed_data->fragmentShader) +
                                              strlen(line) + 1);

        strncat(parsed_data->fragmentShader, line, strlen(parsed_data->fragmentShader) + strlen(line) + 1);
      }
    }
  }
  fclose(file);
  if (!vertexFound || !fragmentFound) {
    perror("Neither vertex or fragment shader source has not found please give a valid shader source file");
    return NULL;
  }
  return parsed_data;
}
