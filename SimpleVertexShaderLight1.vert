#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexColor;
layout(location = 2) in vec3 vertexNormal;

// Output data ; will be interpolated for each fragment.
out vec3 fragmentColor;

out vec3 Pos;
out vec3 Norm;

// Values that stay constant for the whole mesh.
uniform mat4 MVP;
uniform mat4 ModelViewMatrix;

void main(){

	gl_Position = MVP * vec4(vertexPosition_modelspace,1);

  Pos = vec3(ModelViewMatrix*vec4(vertexPosition_modelspace,1.0));
  Norm = vec3(ModelViewMatrix*vec4(vec3(1.0),0.0));
  
	fragmentColor = vertexColor;
}

