#version 400

in  vec4 vPosition;
in  vec4 vColor;
//flat out vec4 color;
out vec4 color;

void main()
{
  gl_Position =vPosition;
  color = vColor;
}