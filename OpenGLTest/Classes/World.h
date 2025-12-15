#pragma once

#include "Chunk.h"
#include <glm/glm.hpp>
#include <vector>
#include "..\ShaderLoader.h"

// World-Settings
const unsigned short CHUNKWIDTH = 16;
const unsigned short CHUNKHEIGHT = 32;

const unsigned int WORLDSIZE = 256;

const unsigned int CHUNKCOUNT = 4;

// Terrain-Generation-Settings
const unsigned int GROUNDTHRESHHOLD = 16;
const unsigned int WATERTHRESHHOLD = 10;

const float CAVENOISEFREQUENCY = 0.08f;
const float CAVENOISEAMPLITUDE = 13.0f;

const float WORLDNOISEFREQUENCY = 0.08f;
const float WORLDNOISEDENSITY = 1.5f;

class World {
public:
	std::vector<Chunk>chunks;

	void Start() {
		for (unsigned int x = 0; x < CHUNKCOUNT; x++) {
			for (unsigned int z = 0; z < CHUNKCOUNT; z++) {
				Chunk chunk = Chunk(glm::vec3(x * CHUNKWIDTH, 0.0f, z * CHUNKWIDTH));
				chunk.Start();
				chunks.push_back(chunk);
			}
		}
	}

	void Render(Shader shader) {
		for (Chunk chunk : chunks) {
			chunk.Render(shader);
		}
	}
};