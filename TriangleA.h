#pragma once

#include "GEObject.h"
#include <vector>
#include <GL\glew.h>

class CTriangleA:
	public CGEObject
{
public:
	CTriangleA();
	~CTriangleA();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Render() override;

protected:
	GLuint programID;
	GLuint handle[3];
	GLuint vaoHandle;
	std::vector<unsigned int> indices;
};

