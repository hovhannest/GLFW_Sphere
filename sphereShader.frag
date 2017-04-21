#version 400

out vec3 Color;

void main(void)
{
   gl_FragColor = vec4(Color, 1.0);
}
