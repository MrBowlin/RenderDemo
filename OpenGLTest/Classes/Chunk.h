#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "..\stb_image.h"
#include "GameObject.h"
#include "TerrainGenerator.h"
#include <thread>
#include "Mesh.h"

const unsigned int WIDTH = 48;
const unsigned int HEIGHT = 48;

class Chunk: public GameObject {
public:
	Mesh mesh;

	unsigned int blockState[WIDTH + 2][HEIGHT][WIDTH + 2];
	TerrainGenerator2D terrain2d = TerrainGenerator2D(13.0f, 0.08f, 32);
	TerrainGenerator3D terrain3d = TerrainGenerator3D(1.5f, 0.05f);

	Chunk(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f)): GameObject(position) {
		
	}

	void Start();

	void Render(Shader shader);
};