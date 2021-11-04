/* shader_program.h
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

#ifndef SHADER_PROGRAM
#define SHADER_PROGRAM

#include "common.h"
#include "parse_shader.h"
#include "map.h"

typedef struct 
{
  GLuint shaderProgramID;
  Map* uniformCache;
} ShaderProgram;

typedef enum {
    UNIFORM_FLOAT = 0,
    UNIFORM_VEC2,
    UNIFORM_VEC3,
    UNIFORM_VEC4,
    UNIFORM_INT,
    UNIFORM_INT_VEC2,
    UNIFORM_INT_VEC3,
    UNIFORM_INT_VEC4,
    UNIFORM_SAMPLER2D
} ShaderUniformDataType;

ShaderProgram*
create_shader_program (const char* shaderFileName);

ShaderProgram*
create_shader_program_vs_fs (const char* vertexSource, const char* fragmentSource);

void
use_shader (ShaderProgram* shaderProgram);

void
set_shader_uniform (ShaderProgram* shaderProgram, const char* uniformName,
                    const void *value, ShaderUniformDataType uniformType);

void
set_shader_uniform_v (ShaderProgram* shaderProgram, const char* uniformName,
                      const void *value, ShaderUniformDataType uniformType, GLuint count);

void
unuse_shader (void);

void
destroy_shader (ShaderProgram** shaderProgram);

#endif
