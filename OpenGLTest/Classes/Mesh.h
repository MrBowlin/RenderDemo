#pragma once

#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "..\ShaderLoader.h"
#include "..\Ressources\Properties\BlockData.h"

enum class Face {
	TOP,
	BOTTOM,
	FRONT,
	BACK,
	LEFT,
	RIGHT
};

class Mesh {
public:
	std::vector<float>positions;
	std::vector<float>normals;
	std::vector<float>texels;
	unsigned int VBO, VAO;
	unsigned int triangleCount;

	Mesh() {
		glGenBuffers(1, &VBO);
		glGenVertexArrays(1, &VAO);
		triangleCount = 0;
	}

	~Mesh() {
		glDeleteBuffers(1, &VBO);
		glDeleteVertexArrays(1, &VAO);
	}

	void CreateBuffer();

	void Render(Shader shader, glm::vec3 position);

	void UpdatePositions(unsigned int x, unsigned int y, unsigned int z, Face face);

	void UpdateNormals(Face face);

	void UpdateTexels(unsigned int blockID, Face face);

	void GetOffset(unsigned int blockID, Face face, float* xOffset, float* yOffset);
};