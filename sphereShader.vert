#version 400
// Input vertex data, different for all executions of this shader.
in vec3 vertexPosition_modelspace;

// Output data ; will be interpolated for each fragment.
out vec2 UV;

uniform mat4 projMatrix;
uniform mat4 mvMatrix;

void main()
{
	gl_Position = projMatrix * mvMatrix * vec4(vertexPosition_modelspace, 1);
}