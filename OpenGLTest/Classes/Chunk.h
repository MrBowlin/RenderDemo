#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "..\stb_image.h"
#include "GameObject.h"
#include "Block.h"
#include "TerrainGenerator.h"
#include <thread>

const unsigned int WIDTH = 48;
const unsigned int HEIGHT = 16;
const unsigned int blockCount = WIDTH * WIDTH * HEIGHT;
const unsigned int trisCount = blockCount * 36;
const unsigned int vertBufferSize = 3 * sizeof(float) * trisCount;
const unsigned int texBufferSize =  2 * sizeof(float) * trisCount;
const unsigned int normBufferSize = 3 * sizeof(float) * trisCount;

class Chunk: public GameObject {
public:
	unsigned int VBO, VAO;

	Block blockData[WIDTH][HEIGHT][WIDTH];
	unsigned int blockState[WIDTH + 2][HEIGHT][WIDTH + 2];
	TerrainGenerator2D terrain2d = TerrainGenerator2D(13.0f, 0.08f, 3);
	TerrainGenerator3D terrain3d = TerrainGenerator3D(1.3f, 0.08f);

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
					if (terrain3d.GetBlockNoise(x, y, z) == 0)
						blockState[x][y][z] = 0;
					else
						blockState[x][y][z] = terrain2d.GetBlockNoise(x, y, z);
				}	
			}
		}
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertBufferSize + texBufferSize + normBufferSize, 0, GL_STATIC_DRAW);

		unsigned int vertBufferIndex = 0;
		unsigned int texBufferIndex = vertBufferSize;
		unsigned int normBufferIndex = vertBufferSize + texBufferSize;
		for (unsigned int x = 0; x < WIDTH; x++) {
			for (unsigned int z = 0; z < WIDTH; z++) {
				for (unsigned int y = 0; y < HEIGHT; y++) {
					glm::vec3 localPos(x, y, z);
					glm::vec3 globalPos = localPos + Position;
					blockData[x][y][z].Init(globalPos, blockState[x + 1][y][z + 1]);
					if (blockState[x + 1][y][z + 1] > 0) {
						if (blockState[x + 1][y][z] == 0)
							blockData[x][y][z].UpdateFace(&vertBufferIndex, &texBufferIndex, &normBufferIndex, Face_Orientation::FRONT,
								&frontVertices, &frontNormals[0],
								static_cast<unsigned int>(frontVertices.size()) * sizeof(float),
								static_cast<unsigned int>(frontNormals.size()) * sizeof(float));
						if (blockState[x + 1][y][z + 2] == 0)
							blockData[x][y][z].UpdateFace(&vertBufferIndex, &texBufferIndex, &normBufferIndex, Face_Orientation::BACK,
								&backVertices, &backNormals[0],
								static_cast<unsigned int>(backVertices.size()) * sizeof(float),
								static_cast<unsigned int>(backNormals.size()) * sizeof(float));
						if (blockState[x][y][z + 1] == 0)
							blockData[x][y][z].UpdateFace(&vertBufferIndex, &texBufferIndex, &normBufferIndex, Face_Orientation::LEFT,
								&leftVertices, &leftNormals[0],
								static_cast<unsigned int>(leftVertices.size()) * sizeof(float),
								static_cast<unsigned int>(leftNormals.size()) * sizeof(float));
						if (blockState[x + 2][y][z + 1] == 0)
							blockData[x][y][z].UpdateFace(&vertBufferIndex, &texBufferIndex, &normBufferIndex, Face_Orientation::RIGHT,
								&rightVertices, &rightNormals[0],
								static_cast<unsigned int>(rightVertices.size()) * sizeof(float),
								static_cast<unsigned int>(rightNormals.size()) * sizeof(float));
						if (y == HEIGHT - 1 || blockState[x + 1][y + 1][z + 1] == 0)
							blockData[x][y][z].UpdateFace(&vertBufferIndex, &texBufferIndex, &normBufferIndex, Face_Orientation::TOP,
								&topVertices, &topNormals[0],
								static_cast<unsigned int>(topVertices.size()) * sizeof(float),
								static_cast<unsigned int>(topNormals.size()) * sizeof(float));
						if (y == 0 || blockState[x + 1][y - 1][z + 1] == 0)
							blockData[x][y][z].UpdateFace(&vertBufferIndex, &texBufferIndex, &normBufferIndex, Face_Orientation::BOTTOM,
								&bottomVertices, &bottomNormals[0],
								static_cast<unsigned int>(bottomVertices.size()) * sizeof(float),
								static_cast<unsigned int>(bottomNormals.size()) * sizeof(float));
					}
				}
			}
		}

		// Buffer-Concept: (PosX PosY PosZ)* (TexX TexY)* (NorX NorY NorZ)*

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(vertBufferSize * 1));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)((vertBufferSize + texBufferSize) * 1));
		glEnableVertexAttribArray(2);

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