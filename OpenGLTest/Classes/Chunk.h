#pragma once
//------ C++ Standard Libraries ------------//
#include <vector>
//------ GLFW, GLM and GLAD ----------------//
//------ Classes ---------------------------//
#include "Mesh.h"
#include "Shader.h"
#include "TerrainGenerator.h"

// Terrain-Generation-Settings
extern const int GROUNDTHRESHHOLD;
extern const int WATERTHRESHHOLD;

extern const float CAVENOISEFREQUENCY;
extern const float CAVENOISEDENSITY;

extern const float WORLDNOISEFREQUENCY;
extern const float WORLDNOISEAMPLITUDE;

class Chunk {
public:
	Mesh* mesh = new Mesh;

	std::vector<uint8_t>blockStates;

	bool ready = false;
	bool updated = false;

	glm::vec3 Position;

	TerrainGenerator2D terrain2d = TerrainGenerator2D(WORLDNOISEAMPLITUDE, WORLDNOISEFREQUENCY, GROUNDTHRESHHOLD);
	TerrainGenerator3D terrain3d = TerrainGenerator3D(CAVENOISEDENSITY, CAVENOISEFREQUENCY);

	Chunk(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f));

	void Start();

	void Render(Shader shader);

	static void UpdateMesh(TerrainGenerator2D* terrain2d, TerrainGenerator3D* terrain3d, std::vector<uint8_t>* blockStates, Mesh* mesh, bool* ready, int xPos, int zPos);
};