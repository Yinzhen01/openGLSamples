#version 330 core
layout(location = 0) in vec3 vPosition;
uniform UniformBlock
{
  float scale;
  vec3 color;
};
void main()
{
  gl_Position = vec4(vPosition * scale, 1.0f);
} 
