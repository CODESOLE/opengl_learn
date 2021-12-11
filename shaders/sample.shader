#vertex

#version 330 core

layout (location = 0) in vec3 aPos;

uniform float time;

void main() {
  gl_Position = vec4(aPos.x, aPos.y + sin(2 * time), aPos.z, 1.0);
}

#fragment

#version 330 core

uniform float time;
in vec3 outPos;

void main() {
  gl_FragColor = vec4(abs(sin(2 * time)), abs(cos(2 * time)), 0.9, 1.0);
}
