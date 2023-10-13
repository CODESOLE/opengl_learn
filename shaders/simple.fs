#version 330 core

in vec3 outPos;
out vec4 outColor;

void main() {
  vec2 st = gl_FragCoord.xy / vec2(outPos.x, outPos.y);
  outColor = vec4(st.x, st.y, 0.0f, 1.0f);
}
