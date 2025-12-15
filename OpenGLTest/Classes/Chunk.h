#pragma once

#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "..\stb_image.h"
#include "TerrainGenerator.h"
#include <thread>
#include "Mesh.h"

// Terrain-Generation-Settings
const unsigned int GROUNDTHRESHHOLD = 96;
const unsigned int WATERTHRESHHOLD = 10;

const float CAVENOISEFREQUENCY = 0.05f;
const float CAVENOISEDENSITY = 13.0f;

const float WORLDNOISEFREQUENCY = 0.08f;
const float WORLDNOISEAMPLITUDE = 1.5f;

class Chunk {
public:
	Mesh* mesh = new Mesh;

	std::vector<uint8_t>blockStates;

	bool ready = false;
	bool updated = false;

	glm::vec3 Position;

	TerrainGenerator2D terrain2d = TerrainGenerator2D(WORLDNOISEAMPLITUDE, WORLDNOISEFREQUENCY, GROUNDTHRESHHOLD);
	TerrainGenerator3D terrain3d = TerrainGenerator3D(CAVENOISEDENSITY, CAVENOISEFREQUENCY);

	Chunk(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f)) {
		Position = position;
	}

	void Start();

	void Render(Shader shader);

	static void UpdateMesh(TerrainGenerator2D* terrain2d, TerrainGenerator3D* terrain3d, std::vector<uint8_t>* blockStates, Mesh* mesh, bool* ready, int xPos, int zPos);
};