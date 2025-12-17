#pragma once
//------ C++ Standard Libraries ------------//
#include <vector>
//------ GLFW, GLM and GLAD ----------------//
#include <glad/glad.h>
#include <glm/glm.hpp>
//------ Classes ---------------------------//
#include "Shader.h"

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

	Mesh();

	~Mesh();

	void CreateBuffer();

	void Render(Shader shader, glm::vec3 position);

	void UpdatePositions(unsigned int x, unsigned int y, unsigned int z, Face face);

	void UpdateNormals(Face face);

	void UpdateTexels(unsigned int blockID, Face face);

	void GetOffset(unsigned int blockID, Face face, float* xOffset, float* yOffset);
};