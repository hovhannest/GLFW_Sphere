#include "Sphere.h"
#include "common\shader.hpp"
#include <glm\glm.hpp>
#include <iostream>
#include <GL\glew.h>
#include "common\controls.hpp"
#include <glm\gtc\matrix_transform.inl>
#include <glm\gtc\constants.inl>


CSphere::CSphere()
{
}


CSphere::~CSphere()
{
}

void CSphere::Init()
{
	m_Angle = glm::vec3(0.0f, 0.0*glm::half_pi<float>(), 0.0);
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
	programID = LoadShaders("SimpleVertexShaderLight1.vert", "SimpleVertexShaderLight.frag");

	// Get a handle for our "MVP" uniform
	MVPID = glGetUniformLocation(programID, "MVP");
	MID = glGetUniformLocation(programID, "ModelViewMatrix");
	
	Vertex v; 
	//Vertex 0
	v.c = glm::vec3(0.4, 0.4, 0.4);

	float radius = 1.0f;
	int i, j;
	int lats = 100;
	int longs = 100;
	int indicator = 1;
	// angular distance between two latitudinal lines
	float deltaPhi = -glm::pi<float>() / longs;
	// angular distance between two longitudinal lines
	float deltaTheta = 2.0f * glm::pi<float>() / lats;
	for (i = 0; i <= lats; i++) {
		// azimuth angles of the two arcs defining the stack (longitudes)
		float theta = i * deltaTheta;
		float thetaPrime = theta + deltaTheta;

		// projection of the first theta in the horizontal plane
		float x0 = cos(theta);
		float y0 = sin(theta);

		// projection of the second theta in the horizontal plane
		float x1 = cos(thetaPrime);
		float y1 = sin(thetaPrime);
		
		for (j = 0; j <= longs; j++) {
			
				v.c = glm::vec3(0.4, 0.4, 0.4);
			
			// polar angle
			float phi = j * deltaPhi;

			// polar vector in a vertical plane 
			float xPolar = cos(phi);
			float yPolar = sin(phi);

			// vertex #2 (theta , phiPrime)
			v.n = glm::vec3(yPolar * x1, yPolar * y1, xPolar);
			v.v = v.n*radius;
			v.u = glm::vec2((float)i / lats, (float)j / longs);
			m_Vertexes.push_back(v);
			//indices.push_back(indicator);
			indicator++;

			v.n = glm::vec3(yPolar * x0, yPolar * y0, xPolar);
			v.v = v.n*radius;
			v.u = glm::vec2((float)i / lats, (float)j / longs);
			m_Vertexes.push_back(v);
			//indices.push_back(indicator);
			indicator++;
						
			indices.push_back(indicator - 3);
			indices.push_back(indicator);
			indices.push_back(indicator - 1);

			indices.push_back(indicator - 2);
			indices.push_back(indicator);
			indices.push_back(indicator - 3);

		}
	}

	glGenVertexArrays(1, &vaoHandle);
	glBindVertexArray(vaoHandle);

	glGenBuffers(4, handle);
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

	glBindBuffer(GL_ARRAY_BUFFER, handle[3]);
	glBufferData(GL_ARRAY_BUFFER, m_Vertexes.size() * sizeof(Vertex), &m_Vertexes[0], GL_STATIC_DRAW);
	//glColorPointer(3, GL_FLOAT, 0, (GLvoid *)((char *)NULL));
	//glEnableClientState(GL_NORMAL_ARRAY);  // Vertex color 
	glEnableVertexAttribArray(2);
}

void CSphere::Release()
{
	// Cleanup VBO and shader
	glDeleteBuffers(3, handle);
	glDeleteProgram(programID);
	glDeleteVertexArrays(1, &vaoHandle);
}

void CSphere::Update(float dt)
{
	//m_Angle += glm::vec3(dt*1.0f);
}

void CSphere::Render()
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
	glUniformMatrix4fv(MVPID, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(MID, 1, GL_FALSE, &ModelMatrix[0][0]);

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

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, handle[3]);
	glVertexAttribPointer(
		2,                                // attribute. No particular reason for 2, but must match the layout in the shader.
		3,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		sizeof(Vertex),                   // stride
		(void*)reinterpret_cast<void *>(offsetof(Vertex, n))                          // array buffer offset
	);

	// Draw the triangle !
	//glDrawArrays(GL_TRIANGLES, 0, 6); // 3 indices starting at 0 -> 1 triangle

	// could be modified to use GL_TRIANGLE_FAN and GL_TRIANGLE_STRIP
	// to draw the poles and the rest of the sphere, 
	// but this will be 2 draw call. Should we??? (draw cal optimizations and such things...)
	/**/glDrawElements(
		GL_TRIANGLES,      // mode
		indices.size(),    // count
		GL_UNSIGNED_INT,   // type
		(void*)0           // element array buffer offset
	);//*/


	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}