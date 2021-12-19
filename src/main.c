/* main.c
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
 */

#include "linmath.h"
#include "shader_program.h"
#include "object.h"
#include "texture.h"
#include "draw.h"

float vertices[] = {
    // positions          // colors           // texture coords
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
};
unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,  // first Triangle
    1, 2, 3   // second Triangle
};

int main(int argc, char **argv) {
  char shader_file[128] = { 0 };
  const char *default_shader_file = "shaders/sample.shader";

  if (argc >= 2) {
    if (argv[1] != NULL && strstr(argv[1], "..\0") == NULL)
      strncpy(shader_file, argv[1], 127);
    else
      strncpy(shader_file, default_shader_file, 127);
    shader_file[127] = '\0';
  } else {
    strncpy(shader_file, default_shader_file, 127);
    shader_file[127] = '\0';
  }

  GLFWwindow *window = init_glfw_glad(640, 480, "NWE");
  int width = 0, height = 0;
  ShaderProgram *shaderProgram = create_shader_program(shader_file);
  Object *object = create_object(vertices, sizeof(vertices), indices,
                                 sizeof(indices), 4, (GLuint[3]){3, 3, 2}, 3);

  int w = 0, h = 0;
  GLuint tex_ = load_texture("shaders/archlogo.png", &w, &h);
  bind_texture_to_object(object, tex_);
  GLuint tex2_ = load_texture("shaders/arch.png", &w, &h);
  bind_texture_to_object(object, tex2_);
  set_shader_uniform(shaderProgram, "tex", (void *)&tex_, UNIFORM_SAMPLER2D);
  set_shader_uniform(shaderProgram, "tex2", (void *)&tex2_, UNIFORM_SAMPLER2D);

  //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  while (!glfwWindowShouldClose(window)) {
    float ratio = calculate_ratio(window, &width, &height);
    UNUSED(ratio);
    gl_clear_color(BLACK_COLOR);
    float timee = (float)glfwGetTime();
    draw(object, shaderProgram);
    set_shader_uniform(shaderProgram, "time", (void *)&timee, UNIFORM_FLOAT);
    glfw_routine(window);
  }

  destroy_object(&object);
  destroy_shader(&shaderProgram);
  destroy_terminate_glfw(window);

  exit(EXIT_SUCCESS);
}
