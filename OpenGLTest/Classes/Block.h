#pragma once

#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "..\ShaderLoader.h"
#include "..\Ressources\Properties\BlockData.h"
#include "TerrainGenerator.h"

enum class Face_Orientation {
	TOP,
	BOTTOM,
	FRONT,
	BACK,
	LEFT,
	RIGHT
};

class Block {
public:
	glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f);

	unsigned int BlockID = 0;

	void Init(glm::vec3 position, unsigned int blockID) {
		Position = position;
		BlockID = blockID;
	}

	void UpdateFace(unsigned int* vertBufferIndex, unsigned int* texBufferIndex, Face_Orientation face, const float vertices[], unsigned int vertSize) {
		ProcessPositionData(vertBufferIndex, vertices, vertSize);
		ProcessTexelData(face, texBufferIndex);
	}

private:
	void AddToBuffer(unsigned int* bufferIndex, float indices[], unsigned int indexSize) {
		glBufferSubData(GL_ARRAY_BUFFER, *bufferIndex, indexSize, indices);
		*bufferIndex += indexSize;
	}

	void ProcessPositionData(unsigned int* bufferIndex, const float vertices[], unsigned int vertSize) {
		float positions[6 * 3];
		for (unsigned int i = 0; i < 6 * 3; i += 3) {
			positions[i] = Position.x + vertices[i];
			positions[i + 1] = Position.y + vertices[i + 1];
			positions[i + 2] = Position.z + vertices[i + 2];
		}
		AddToBuffer(bufferIndex, positions, vertSize);
	}

	void ProcessTexelData(Face_Orientation face, unsigned int* bufferIndex) {
		float xOffset;
		float yOffset;
		GetOffset(face, &xOffset, &yOffset);
		
		float texels[] = {
			0.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 1.0f,
			1.0f, 1.0f,
			0.0f, 1.0f,
			0.0f, 0.0f,
		};
		for (unsigned int i = 0; i < 6 * 2; i += 2) {
			texels[i] = (texels[i] + xOffset) / 16.0f;
			texels[i + 1] = (texels[i + 1] + 15 - yOffset) / 16.0f;
		}
		AddToBuffer(bufferIndex, texels, sizeof(texels));
	}

	void GetOffset(Face_Orientation face, float* xOffset, float* yOffset) {
		int textureID;
		switch (BlockID)
		{
		case 1:		// Dirt
			textureID = 3;
			break;
		case 2:		// Stone
			textureID = 2;
			break;
		case 3:		// Grass
			if (face == Face_Orientation::TOP)
				textureID = 1;
			else if (face == Face_Orientation::BOTTOM)
				textureID = 3;
			else
				textureID = 4;
			break;
		case 4:		// Cobblestone
			textureID = 17;
			break;
		case 5:		// Log
			if (face == Face_Orientation::TOP || face == Face_Orientation::BOTTOM)
				textureID = 22;
			else
				textureID = 21;
			break;
		case 6:		// Sand
			textureID = 19;
			break;
		case 7:		// Planks
			textureID = 5;
			break;
		default:
			*xOffset = 10.0f;
			*yOffset = 14.0f;
			return;
		}
		*xOffset = texCoords[textureID * 2 - 2];
		*yOffset = texCoords[textureID * 2 - 1];
		return;
	}
};