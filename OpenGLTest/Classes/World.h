#pragma once

#include "Chunk.h"
#include <glm/glm.hpp>
#include <vector>
#include "..\ShaderLoader.h"

// World-Settings
const unsigned short CHUNKWIDTH = 18;
const unsigned short CHUNKHEIGHT = 128;

const unsigned int WORLDSIZE = 256;

const unsigned int CHUNKCOUNT = 8;

class World {
public:
	std::vector<Chunk*>chunks;

	void Start() {
		for (unsigned int x = 0; x < CHUNKCOUNT; x++) {
			for (unsigned int z = 0; z < CHUNKCOUNT; z++) {
				Chunk *chunk = new Chunk(glm::vec3(x * (CHUNKWIDTH - 2), 0.0f, z * (CHUNKWIDTH - 2)));
				chunk->Start();
				chunks.push_back(chunk);
			}
		}
	}

	void Render(Shader shader) {
		for (Chunk* chunk : chunks) {
			chunk->Render(shader);
		}
	}
};