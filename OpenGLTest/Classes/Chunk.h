#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "..\stb_image.h"
#include "GameObject.h"
#include "Block.h"

const unsigned int WIDTH = 16;
const unsigned int HEIGHT = 32;
const unsigned int blockCount = WIDTH * WIDTH * HEIGHT;

class Chunk: public GameObject {
public:
	Block blockData[WIDTH][HEIGHT][WIDTH];
    unsigned int VBO, VAO;

	Chunk(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f)): GameObject(position) {
        glGenBuffers(1, &VBO);
        glGenVertexArrays(1, &VAO);
	}

    ~Chunk() {
        glDeleteBuffers(1, &VBO);
    }

	void Start() {
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, blockCount * 30 * 6, 0, GL_STATIC_DRAW);

		unsigned int bufferIndex = 0;
		for (unsigned int x = 0; x < WIDTH; x++) {
			for (unsigned int z = 0; z < WIDTH; z++) {
				for (unsigned int y = 0; y < HEIGHT; y++) {
					glm::vec3 localPos(x, y, z);
					glm::vec3 globalPos = localPos + Position;
					blockData[x][y][z] = Block(globalPos);
					blockData[x][y][z].UpdateFaces(&bufferIndex);
				}
			}
		}

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glBindVertexArray(0);
	}

	void Render(Shader shader) {
		glBindVertexArray(VAO);
		for (unsigned int x = 0; x < WIDTH; x++) {
			for (unsigned int z = 0; z < WIDTH; z++) {
				for (unsigned int y = 0; y < HEIGHT; y++) {
					glm::mat4 model = glm::mat4(1.0f);
					model = glm::translate(model, blockData[x][y][z].Position);
					shader.setMat4("model", model);
					glDrawArrays(GL_TRIANGLES, 0, 36);
				}
			}
		}
	}
};