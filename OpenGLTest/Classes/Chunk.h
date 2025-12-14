#pragma once

#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "..\stb_image.h"
#include "GameObject.h"
#include "TerrainGenerator.h"
#include <thread>
#include "Mesh.h"

const unsigned int WIDTH = 16;
const unsigned int HEIGHT = 32;

class Chunk: public GameObject {
public:
	Mesh mesh;

	std::vector<unsigned int>blockStates;

	bool ready = false;
	bool updated = false;
	
	TerrainGenerator2D terrain2d = TerrainGenerator2D(13.0f, 0.08f, 3);
	TerrainGenerator3D terrain3d = TerrainGenerator3D(1.5f, 0.05f);

	Chunk(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f)) : GameObject(position){}

	void Start();

	void Render(Shader shader);

	static void UpdateMesh(TerrainGenerator2D *terrain2d, TerrainGenerator3D *terrain3d, std::vector<unsigned int>* blockStates, Mesh *mesh, bool* ready);
};