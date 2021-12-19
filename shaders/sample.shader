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
  gl_Position = vec4(aPos.x, aPos.y + sin(2 * time) / 2, aPos.z, 1.0);
  outPos = aPos;
  outCol = aCol;
  outUV = aUV;
}

#fragment

#version 330 core

uniform float time;
in vec3 outPos;
in vec3 outCol;
in vec2 outUV;

uniform sampler2D tex;
uniform sampler2D tex2;

void main() {
  vec2 u_dimensions = vec2(0.5f, 0.5f);
  float u_radius = 0.1;
  vec2 coords = outUV * u_dimensions;
  if (length(coords - vec2(0)) < u_radius ||
      length(coords - vec2(0, u_dimensions.y)) < u_radius ||
      length(coords - vec2(u_dimensions.x, 0)) < u_radius ||
      length(coords - u_dimensions) < u_radius) {
    discard;
  }

  vec4 img = mix(texture(tex, outUV), texture(tex2, outUV), 0.3);

  gl_FragColor = img * vec4(abs(sin(2 * time)), abs(cos(2 * time)), 0.9, 1.0);
}
