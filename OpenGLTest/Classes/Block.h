#pragma once

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "..\ShaderLoader.h"

enum Block_Type {
	AIR,
	DIRT,
	GRASS
};

enum Face {
	TOP,
	BOTTOM,
	RIGHT,
	LEFT,
	FRONT,
	BACK
};

class Block {
public:
	glm::vec3 Position;

	Block_Type BlockID;

	Block(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), Block_Type blockID = DIRT) {
		Position = position;
		BlockID = blockID;
	}

	void UpdateFaces(unsigned int* bufferIndex) {
		if (BlockID != AIR) {
			RenderFace(TOP, bufferIndex);
			RenderFace(BOTTOM, bufferIndex);
			RenderFace(RIGHT, bufferIndex);
			RenderFace(LEFT, bufferIndex);
			RenderFace(FRONT, bufferIndex);
			RenderFace(BACK, bufferIndex);
		}
	}

	void RenderFace(Face orientation, unsigned int* bufferIndex) {
		switch (orientation)
		{
		case TOP:
		{
			float vertices[] = {
				-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
				0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
				0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
				0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
				-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
				-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			};
			glBufferSubData(GL_ARRAY_BUFFER, *bufferIndex, sizeof(vertices), vertices);
			*bufferIndex += sizeof(vertices);
		}
			break;
		case BOTTOM:
		{
			float vertices[] = {
				-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
				0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
				0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
				0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
				-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
				-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			};
			glBufferSubData(GL_ARRAY_BUFFER, *bufferIndex, sizeof(vertices), vertices);
			*bufferIndex += sizeof(vertices);
		}
			break;
		case RIGHT:
		{
			float vertices[] = {
				0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
				0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
				0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
				0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
				0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
				0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			};
			glBufferSubData(GL_ARRAY_BUFFER, *bufferIndex, sizeof(vertices), vertices);
			*bufferIndex += sizeof(vertices);
		}
			break;
		case LEFT:
		{
			float vertices[] = {
				-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
				-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
				-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
				-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
				-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
				-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			};
			glBufferSubData(GL_ARRAY_BUFFER, *bufferIndex, sizeof(vertices), vertices);
			*bufferIndex += sizeof(vertices);
		}
			break;
		case FRONT:
		{
			float vertices[] = {
				-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
				0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
				0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
				0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
				-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
				-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
			};
			glBufferSubData(GL_ARRAY_BUFFER, *bufferIndex, sizeof(vertices), vertices);
			*bufferIndex += sizeof(vertices);
		}
			break;
		case BACK:
		{
			float vertices[] = {
				-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
				0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
				0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
				0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
				-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
				-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
			};
			glBufferSubData(GL_ARRAY_BUFFER, *bufferIndex, sizeof(vertices), vertices);
			*bufferIndex += sizeof(vertices);
		}
			break;
		default:
			break;
		}
	}
};