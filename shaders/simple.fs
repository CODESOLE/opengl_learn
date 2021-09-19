#version 330 core

in vec3 outPos;

void main()
{
  vec2 st = gl_FragCoord.xy / vec2(outPos.x, outPos.y);
  gl_FragColor = vec4(st.x, st.y, 0.0f, 1.0f);
}
