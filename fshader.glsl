#version 400

in float Transp;
layout ( location = 0 ) out vec4 FragColor;
void main()
{
  FragColor = vec4(1.0f, 1.0f, 0.0f,1.0f);
  FragColor.a *= Transp;
  FragColor.g *= Transp;
}