#pragma once

#include <glm/glm.hpp>
#include "..\ShaderLoader.h"

class GameObject {
public:
	glm::vec3 Position;
	glm::vec3 Rotation;
	glm::vec3 Scale;

	GameObject(
		glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), 
		glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f), 
		glm::vec3 scale = glm::vec3(0.0f, 0.0f, 0.0f)) 
	{
		Position = position;
		Rotation = rotation;
		Scale = scale;
	}

	virtual void Start() {

	}
	virtual void Update(float deltaTime) {

	}
	virtual void Render(Shader shader) {

	}
};