#pragma once
//------ C++ Standard Libraries ------------//
#include <vector>
#include <iostream>
//------ GLFW, GLM and GLAD ----------------//
#include <glm/glm.hpp>
//------ Classes ---------------------------//
#include "Shader.h"
#include "Chunk.h"
#include "..\Settings\WorldSettings.h"
#include "ThreadPool.h"
#include "TerrainGenerator.h"

namespace World {
	std::vector<Chunk*>chunks;
	ThreadPool threadPool = ThreadPool(8);
	TerrainGenerator2D worldGenerator = TerrainGenerator2D(
		WorldSettings::WORLDNOISEAMPLITUDE,
		WorldSettings::WORLDNOISEFREQUENCY,
		WorldSettings::HEIGHTOFFSET,
		WorldSettings::WORLDNOISEOCTAVES,
		WorldSettings::WORLDNOISEPERSISTANCE,
		WorldSettings::AMPLIFIERSTRENGTH);
	TerrainGenerator3D caveGenerator = TerrainGenerator3D(
		WorldSettings::CAVENOISEDENSITY,
		WorldSettings::CAVENOISEFREQUENCY,
		WorldSettings::CAVENOISEOCTAVES,
		WorldSettings::CAVENOISEPERSISTANCE);

	void Start() {
		for (unsigned int x = 0; x < WorldSettings::CHUNKCOUNT; x++) {
			for (unsigned int z = 0; z < WorldSettings::CHUNKCOUNT; z++) {
				Chunk* chunk = new Chunk(glm::vec3(x * (WorldSettings::CHUNKWIDTH - 2), 0.0f, z * (WorldSettings::CHUNKWIDTH - 2)));
				chunks.push_back(chunk);
				threadPool.enqueue([chunk]{
					chunk->UpdateData(&worldGenerator, &caveGenerator);
					chunk->UpdateMesh();
					chunk->ready = true;
				});
			}
		}
	}

	void Render(Shader shader) {
		shader.use();
		shader.setVec3("lightColor", Game::lightColor);
		shader.setVec3("lightDirection", Game::lightDirection);
		shader.setFloat("ambientStrength", Game::ambientStrength);

		for (Chunk* chunk : chunks) {
			chunk->Render(shader);
		}
	}

	void Stop() {
		for (Chunk* chunk : chunks) {
			delete chunk;
		}
	}
};