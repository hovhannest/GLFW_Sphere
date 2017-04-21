#include "CubeA.h"
#include "common\shader.hpp"
#include <glm\glm.hpp>
#include <iostream>
#include <GL\glew.h>
#include "common\controls.hpp"
#include <glm\gtc\matrix_transform.inl>


CCubeA::CCubeA()
{
}


CCubeA::~CCubeA()
{
}

void CCubeA::Init()
{
	m_Angle = glm::vec3(10.0f);
	// Initial Field of View
	float initialFoV = 45.0f;
	position = glm::vec3(0, 0, 3);
	horizontalAngle = 3.14f;
	verticalAngle = 0.0f;
	// Direction : Spherical coordinates to Cartesian coordinates conversion
	glm::vec3 direction(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);	
	// Right vector
	glm::vec3 right = glm::vec3(
		sin(horizontalAngle - 3.14f / 2.0f),
		0,
		cos(horizontalAngle - 3.14f / 2.0f)
	);

	// Up vector
	glm::vec3 up = glm::cross(right, direction);
	m_ViewMatrix = glm::lookAt(
		position,           // Camera is here
		position + direction, // and looks here : at the same position, plus "direction"
		up                  // Head is up (set to 0,-1,0 to look upside-down)
	);
	m_ProjectionMatrix = glm::perspective(initialFoV, 4.0f / 3.0f, 0.1f, 100.0f);
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	programID = LoadShaders("SimpleVertexShader1.vert", "SimpleFragmentShader1.frag");

	// Get a handle for our "MVP" uniform
	MatrixID = glGetUniformLocation(programID, "MVP");

	float side2 = 0.5f;
	
	Vertex v; 
	//Vertex 0
	v.v = glm::vec3(-side2, -side2, side2);
	v.c = glm::vec3(0.0, 0.0, 1.0);
	m_Vertexes.push_back(v);
	//Vertex 1
	v.v = glm::vec3(side2, -side2, side2);
	v.c = glm::vec3(1.0, 0.0, 1.0);
	m_Vertexes.push_back(v);
	//Vertex 2
	v.v = glm::vec3(side2, side2, side2);
	v.c = glm::vec3(1.0, 1.0, 1.0);
	m_Vertexes.push_back(v);
	//Vertex 3
	v.v = glm::vec3(-side2, side2, side2);
	v.c = glm::vec3(0.0, 1.0, 1.0);
	m_Vertexes.push_back(v);
	//Vertex 4
	v.v = glm::vec3(-side2, -side2, -side2);
	v.c = glm::vec3(0.0, 0.0, 0.0);
	m_Vertexes.push_back(v);
	//Vertex 5
	v.v = glm::vec3(side2, -side2, -side2);
	v.c = glm::vec3(1.0, 0.0, 0.0);
	m_Vertexes.push_back(v);
	//Vertex 6
	v.v = glm::vec3(side2, side2, -side2);
	v.c = glm::vec3(1.0, 1.0, 0.0);
	m_Vertexes.push_back(v);
	//Vertex 7
	v.v = glm::vec3(-side2, side2, -side2);
	v.c = glm::vec3(0.0, 1.0, 0.0);
	m_Vertexes.push_back(v);
	
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);

	indices.push_back(0);
	indices.push_back(2);
	indices.push_back(3);

	indices.push_back(1);
	indices.push_back(5);
	indices.push_back(6);

	indices.push_back(1);
	indices.push_back(6);
	indices.push_back(2);

	indices.push_back(4);
	indices.push_back(7);
	indices.push_back(6);

	indices.push_back(4);
	indices.push_back(6);
	indices.push_back(5);

	indices.push_back(0);
	indices.push_back(3);
	indices.push_back(7);

	indices.push_back(0);
	indices.push_back(7);
	indices.push_back(4);

	indices.push_back(3);
	indices.push_back(2);
	indices.push_back(6);

	indices.push_back(3);
	indices.push_back(6);
	indices.push_back(7);

	indices.push_back(0);
	indices.push_back(4);
	indices.push_back(5);

	indices.push_back(0);
	indices.push_back(5);
	indices.push_back(1);

	glGenVertexArrays(1, &vaoHandle);
	glBindVertexArray(vaoHandle);

	glGenBuffers(3, handle);
	glBindBuffer(GL_ARRAY_BUFFER, handle[0]);
	glBufferData(GL_ARRAY_BUFFER, m_Vertexes.size()*sizeof(Vertex), &m_Vertexes[0], GL_STATIC_DRAW);
	//glVertexPointer(3, GL_FLOAT, 2*sizeof(float), (GLvoid *)((char *)NULL));
	glEnableClientState(GL_VERTEX_ARRAY);  // Vertex position

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle[2]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
	//glVertexPointer(1, GL_UNSIGNED_INT, 0, (GLvoid *)((char *)NULL));
	//glEnableClientState(GL_INDEX_ARRAY);  // Vertex position

	glBindBuffer(GL_ARRAY_BUFFER, handle[1]);
	glBufferData(GL_ARRAY_BUFFER, m_Vertexes.size() * sizeof(Vertex), &m_Vertexes[0], GL_STATIC_DRAW);
	//glColorPointer(3, GL_FLOAT, 0, (GLvoid *)((char *)NULL));
	glEnableClientState(GL_COLOR_ARRAY);  // Vertex color 
}

void CCubeA::Release()
{
	// Cleanup VBO and shader
	glDeleteBuffers(3, handle);
	glDeleteProgram(programID);
	glDeleteVertexArrays(1, &vaoHandle);
}

void CCubeA::Update(float dt)
{
	m_Angle += glm::vec3(dt*1.0f);
}

void CCubeA::Render()
{
	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 ProjectionMatrix = m_ProjectionMatrix;
	glm::mat4 ViewMatrix = m_ViewMatrix;
	glm::mat4 ModelMatrix = glm::mat4(1.0f);
	ModelMatrix = glm::rotate(ModelMatrix, m_Angle[0], glm::vec3(1.0f, 0.0f, 0.0f));
	ModelMatrix = glm::rotate(ModelMatrix, m_Angle[1], glm::vec3(0.0f, 1.0f, 0.0f));
	ModelMatrix = glm::rotate(ModelMatrix, m_Angle[2], glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

	// Send our transformation to the currently bound shader, 
	// in the "MVP" uniform
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

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
		sizeof(Vertex),     // stride
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
		sizeof(Vertex),                   // stride
		(void*)reinterpret_cast<void *>(offsetof(Vertex, c))                          // array buffer offset
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