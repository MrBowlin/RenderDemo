#pragma once
//------ C++ Standard Libraries ------------//
#include <vector>
#include <iostream>
#include <unordered_map>
//------ GLFW, GLM and GLAD ----------------//
#include <glm/glm.hpp>
//------ Classes ---------------------------//
#include "Shader.h"
#include "Chunk.h"
#include "..\Settings\WorldSettings.h"
#include "ThreadPool.h"
#include "TerrainGenerator.h"

namespace World {
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
	std::unordered_map<int, Chunk*> chunkMap;

	int GetChunkKey(int x, int z) {
		int keyX = x % (GameSettings::LOADINGDISTANCE * 2);
		int keyZ = (z % (GameSettings::LOADINGDISTANCE * 2)) * GameSettings::LOADINGDISTANCE * 2;
		std::cout << x << " : " << z << "\n";
		std::cout << keyX << " : " << keyZ << "\n";
		std::cout << keyX + keyZ << "\n";
		return keyX + keyZ;
	}

	void Start() {
		for (int x = 0; x < GameSettings::LOADINGDISTANCE * 2; x++) {
			for (int z = 0; z < GameSettings::LOADINGDISTANCE * 2; z++) {
				Chunk* chunk = new Chunk(glm::vec3(
					(x - GameSettings::LOADINGDISTANCE) * (WorldSettings::CHUNKWIDTH - 2),
					0.0f, 
					(z - GameSettings::LOADINGDISTANCE) * (WorldSettings::CHUNKWIDTH - 2)));
				//std::cout << (x - GameSettings::CHUNKRENDERDISTANCE) * (WorldSettings::CHUNKWIDTH - 2) << " : ";
				//std::cout << (z - GameSettings::CHUNKRENDERDISTANCE) * (WorldSettings::CHUNKWIDTH - 2) << "\n";
				
				int chunkKey = GetChunkKey(x, z);
				chunkMap.insert({ chunkKey, chunk });
				threadPool.enqueue([chunk]{
					chunk->UpdateData(&worldGenerator, &caveGenerator);
					chunk->UpdateMesh();
					chunk->ready = true;
				});
			}
		}
	}

	void Update() {

	}

	void Render(Shader shader) {
		shader.use();
		shader.setVec3("lightColor", Game::lightColor);
		shader.setVec3("lightDirection", Game::lightDirection);
		shader.setFloat("ambientStrength", Game::ambientStrength);

		for (auto chunk : chunkMap) {
			chunk.second->Render(shader);
		}
	}

	void Stop() {
		for (auto chunk : chunkMap) {
			delete chunk.second;
		}
		chunkMap.clear();
	}
};