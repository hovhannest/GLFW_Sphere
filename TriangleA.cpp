#include "TriangleA.h"
#include <GL\glew.h>
#include "common\shader.hpp"



CTriangleA::CTriangleA()
{
}


CTriangleA::~CTriangleA()
{
}

void CTriangleA::Init()
{
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	programID = LoadShaders("SimpleVertexShader.vert", "SimpleFragmentShader.frag");


	static const GLfloat g_vertex_buffer_data[] = {
		-0.8f, -0.8f, 0.0f,
		0.8f, -0.8f, 0.0f,
		0.0f,  0.8f, 0.0f,
		-0.5f, -0.5f, 0.5f,
		0.5f, -0.5f, 0.5f,
		0.0f,  0.5f, 0.5f,
	};

	static const GLfloat g_color_buffer_data[] = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f,  0.0f, 1.0f,
		0.0f,  0.0f, 1.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
	};

	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(3);
	indices.push_back(3);
	indices.push_back(4);
	indices.push_back(5);

	glGenVertexArrays(1, &vaoHandle);
	glBindVertexArray(vaoHandle);

	glGenBuffers(3, handle);
	glBindBuffer(GL_ARRAY_BUFFER, handle[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	glVertexPointer(3, GL_FLOAT, 0, (GLvoid *)((char *)NULL));
	glEnableClientState(GL_VERTEX_ARRAY);  // Vertex position

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle[2]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
	glVertexPointer(1, GL_UNSIGNED_INT, 0, (GLvoid *)((char *)NULL));
	glEnableClientState(GL_INDEX_ARRAY);  // Vertex position

	glBindBuffer(GL_ARRAY_BUFFER, handle[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
	glColorPointer(3, GL_FLOAT, 0, (GLvoid *)((char *)NULL));
	glEnableClientState(GL_COLOR_ARRAY);  // Vertex color 
}

void CTriangleA::Release()
{
	// Cleanup VBO and shader
	glDeleteBuffers(3, handle);
	glDeleteProgram(programID);
	glDeleteVertexArrays(1, &vaoHandle);
}

void CTriangleA::Update(float dt)
{
}

void CTriangleA::Render()
{
	// Use our shader
	glUseProgram(programID);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, handle[0]);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// 2nd attribute buffer : colors
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, handle[1]);
	glVertexAttribPointer(
		1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
		3,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	// Draw the triangle !
	//glDrawArrays(GL_TRIANGLES, 0, 6); // 3 indices starting at 0 -> 1 triangle

	/**/glDrawElements(
		GL_TRIANGLES,      // mode
		indices.size(),    // count
		GL_UNSIGNED_INT,   // type
		(void*)0           // element array buffer offset
	);//*/


	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}