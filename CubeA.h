#pragma once

#include "GEObject.h"
#include <GL\glew.h>
#include <vector>


class CCubeA:
	public CGEObject
{
public:
	CCubeA();
	~CCubeA();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Render() override;

protected:
	GLuint programID;
	GLuint handle[3];
	GLuint vaoHandle;
	std::vector<unsigned int> indices;
	std::vector<Vertex> m_Vertexes;
	GLuint MatrixID;

	glm::mat4 m_ViewMatrix;
	glm::mat4 m_ProjectionMatrix; 
	glm::vec3 position;
	glm::vec3 m_Angle;

	// Initial horizontal angle : toward -Z
	float horizontalAngle;
	// Initial vertical angle : none
	float verticalAngle;
};

