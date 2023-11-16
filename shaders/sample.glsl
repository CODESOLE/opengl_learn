#vertex

#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;
layout (location = 2) in vec2 aUV;

uniform float time;
out vec3 outPos;
out vec3 outCol;
out vec2 outUV;

void main() {
  outPos = aPos;
  outCol = aCol;
  outUV = aUV;
  gl_Position = vec4(aPos.x, aPos.y + sin(2 * time) / 2, aPos.z, 1.0);
}

#fragment

#version 330 core

in vec3 outPos;
in vec3 outCol;
in vec2 outUV;
out vec4 outColor;

uniform sampler2D tex;
uniform sampler2D tex2;

void main() {
  vec4 img = mix(texture(tex, outUV), texture(tex2, outUV), 0.5);

  outColor = img * vec4(outCol, 1.0);
}
