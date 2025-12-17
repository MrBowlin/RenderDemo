#pragma once
//------ C++ Standard Libraries ------------//
#include <vector>
//------ GLFW, GLM and GLAD ----------------//
//------ Classes ---------------------------//
#include "Mesh.h"
#include "Shader.h"
#include "TerrainGenerator.h"
#include "..\Settings\WorldSettings.h"

class Chunk {
public:
	Mesh* mesh = new Mesh;

	std::vector<unsigned short>blockStates;

	bool ready = false;
	bool updated = false;

	glm::vec3 Position;

	Chunk(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f));

	~Chunk() {
		delete mesh;
	}

	void Render(Shader shader);

	void UpdateData(TerrainGenerator2D* worldGenerator, TerrainGenerator3D* caveGenerator);

	void UpdateMesh();
};