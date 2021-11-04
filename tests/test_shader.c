#include "linmath.h"
#include "shader_program.h"
#include "object.h"
#include "draw.h"
#include <assert.h>

float vertices[] = {
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left
};
unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,  // first Triangle
    1, 2, 3   // second Triangle
};

int main(void)
{
 /*
  GLFWwindow* window = init_glfw_glad (640, 480, "NWE");
  int width = 0, height = 0;

  //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  do
    {
      float ratio = calculate_ratio (window, &width, &height);
      UNUSED (ratio);
      glfw_routine (window);
    }while (0);
  destroy_terminate_glfw (window);
 */
  exit(EXIT_SUCCESS);
}
