#pragma once

#include "IReusable.h"
#include "IDrawable.h"
#include <glm\glm.hpp>


class CGEObject:
	public IReusable,
	public IDrawable
{
public:
	CGEObject();
	~CGEObject();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Render() override;
};

#pragma pack(push, 0)
typedef struct
{
	glm::vec3 v;
	glm::vec3 n;
	glm::vec3 c;
	glm::vec2 u;
}
Vertex;
#pragma pack(pop)
