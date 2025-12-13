#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "..\stb_image.h"
#include "GameObject.h"
#include "Block.h"
#include "TerrainGenerator.h"

const unsigned int WIDTH = 20;
const unsigned int HEIGHT = 20;
const unsigned int blockCount = WIDTH * WIDTH * HEIGHT;
const unsigned int trisCount = blockCount * 36;
const unsigned int vertBufferSize = 3 * sizeof(float) * trisCount;
const unsigned int texBufferSize =  2 * sizeof(float) * trisCount;

class Chunk: public GameObject {
public:
	unsigned int VBO, VAO;

	Block blockData[WIDTH][HEIGHT][WIDTH];
	unsigned int blockState[WIDTH + 2][HEIGHT][WIDTH + 2];
	TerrainGenerator2D terrain2d = TerrainGenerator2D(10.0f, 0.1f);
	TerrainGenerator3D terrain3d = TerrainGenerator3D(1.0f, 0.1f);

	Chunk(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f)): GameObject(position) {
		glGenBuffers(1, &VBO);
		glGenVertexArrays(1, &VAO);
	}

    ~Chunk() {
		glDeleteBuffers(1, &VBO);
		glDeleteVertexArrays(1, &VAO);
    }

	void Start() {
		for (unsigned int x = 0; x < WIDTH + 2; x++) {
			for (unsigned int z = 0; z < WIDTH + 2; z++) {
				for (unsigned int y = 0; y < HEIGHT; y++) {
					blockState[x][y][z] = terrain3d.GetBlockNoise(x, y, z);
				}
			}
		}
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertBufferSize + texBufferSize, 0, GL_STATIC_DRAW);

		unsigned int vertBufferIndex = 0;
		unsigned int texBufferIndex = vertBufferSize;
		for (unsigned int x = 0; x < WIDTH; x++) {
			for (unsigned int z = 0; z < WIDTH; z++) {
				for (unsigned int y = 0; y < HEIGHT; y++) {
					glm::vec3 localPos(x, y, z);
					glm::vec3 globalPos = localPos + Position;
					blockData[x][y][z].Init(globalPos, blockState[x + 1][y][z + 1]);
					if (blockState[x + 1][y][z + 1] > 0) {
						if (blockState[x + 1][y][z] == 0)
							blockData[x][y][z].UpdateFace(&vertBufferIndex, &texBufferIndex, Face_Orientation::FRONT, frontVertices, sizeof(frontVertices));
						if (blockState[x + 1][y][z + 2] == 0)
							blockData[x][y][z].UpdateFace(&vertBufferIndex, &texBufferIndex, Face_Orientation::BACK, backVertices, sizeof(backVertices));
						if (blockState[x][y][z + 1] == 0)
							blockData[x][y][z].UpdateFace(&vertBufferIndex, &texBufferIndex, Face_Orientation::LEFT, leftVertices, sizeof(leftVertices));
						if (blockState[x + 2][y][z + 1] == 0)
							blockData[x][y][z].UpdateFace(&vertBufferIndex, &texBufferIndex, Face_Orientation::RIGHT, rightVertices, sizeof(rightVertices));
						if (y == HEIGHT - 1 || blockState[x + 1][y + 1][z + 1] == 0)
							blockData[x][y][z].UpdateFace(&vertBufferIndex, &texBufferIndex, Face_Orientation::TOP, topVertices, sizeof(topVertices));
						if (y == 0 || blockState[x + 1][y - 1][z + 1] == 0)
							blockData[x][y][z].UpdateFace(&vertBufferIndex, &texBufferIndex, Face_Orientation::BOTTOM, bottomVertices, sizeof(bottomVertices));
					}
				}
			}
		}

		// Buffer-Concept: (PosX PosY PosZ)* (TexX TexY)*

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(6 * 6 * 3 * sizeof(float) * blockCount));
		//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), &vertBufferSize);
		glEnableVertexAttribArray(1);

		glBindVertexArray(0);
	}

	void Render(Shader shader) {
		shader.setInt("texture", 0);
		glBindVertexArray(VAO);
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, Position);
		shader.setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, trisCount);
	}
};