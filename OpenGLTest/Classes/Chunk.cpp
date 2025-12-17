#include "Chunk.h"
//------ C++ Standard Libraries ------------//
#include <thread>
#include <iostream>
//------ GLFW, GLM and GLAD ----------------//
//------ Classes ---------------------------//
#include "..\Settings\WorldSettings.h"

Chunk::Chunk(glm::vec3 position) {
	Position = position;
}

void Chunk::UpdateData(TerrainGenerator2D* worldGenerator, TerrainGenerator3D* caveGenerator) {
	if (blockStates.size() > 0)
		blockStates.clear();
	for (int x = 0; x < WorldSettings::CHUNKWIDTH; x++) {
		for (int z = 0; z < WorldSettings::CHUNKWIDTH; z++) {
			for (int y = 0; y < WorldSettings::CHUNKHEIGHT; y++) {
				int xPos = static_cast<int>(Position.x);
				int zPos = static_cast<int>(Position.z);
				if (caveGenerator->GetBlockNoise(xPos + x - 1, y, zPos + z - 1) == 0) {
					blockStates.push_back(0);
				}
				else {
					blockStates.push_back(worldGenerator->GetBlockNoise(xPos + x - 1, y, zPos + z - 1));
				}
			}
		}
	}
}
	
void Chunk::UpdateMesh() {
	unsigned int currentBlock = (1 + WorldSettings::CHUNKWIDTH) * WorldSettings::CHUNKHEIGHT;
	for (unsigned int x = 1; x < WorldSettings::CHUNKWIDTH - 1; x++) {
		for (unsigned int z = 1; z < WorldSettings::CHUNKWIDTH - 1; z++) {
			for (unsigned int y = 0; y < WorldSettings::CHUNKHEIGHT; y++) {
				unsigned short blockID = blockStates.at(currentBlock);
				if (blockID > 0) {
					if (blockStates.at(currentBlock - WorldSettings::CHUNKHEIGHT) == 0) {
						mesh->UpdatePositions(x - 1, y, z - 1, Face::FRONT);
						mesh->UpdateNormals(Face::FRONT);
						mesh->UpdateTexels(blockID, Face::FRONT);
					}
					if (blockStates.at(currentBlock + WorldSettings::CHUNKHEIGHT) == 0) {
						mesh->UpdatePositions(x - 1, y, z - 1, Face::BACK);
						mesh->UpdateNormals(Face::BACK);
						mesh->UpdateTexels(blockID, Face::BACK);
					}
					if (blockStates.at(currentBlock - WorldSettings::CHUNKHEIGHT * WorldSettings::CHUNKWIDTH) == 0) {
						mesh->UpdatePositions(x - 1, y, z - 1, Face::LEFT);
						mesh->UpdateNormals(Face::LEFT);
						mesh->UpdateTexels(blockID, Face::LEFT);
					}
					if (blockStates.at(currentBlock + WorldSettings::CHUNKHEIGHT * WorldSettings::CHUNKWIDTH) == 0) {
						mesh->UpdatePositions(x - 1, y, z - 1, Face::RIGHT);
						mesh->UpdateNormals(Face::RIGHT);
						mesh->UpdateTexels(blockID, Face::RIGHT);
					}
					if (y == WorldSettings::CHUNKHEIGHT - 1 || blockStates.at(currentBlock + 1) == 0) {
						mesh->UpdatePositions(x - 1, y, z - 1, Face::TOP);
						mesh->UpdateNormals(Face::TOP);
						mesh->UpdateTexels(blockID, Face::TOP);
					}
					if (y == 0 || blockStates.at(currentBlock - 1) == 0) {
						mesh->UpdatePositions(x - 1, y, z - 1, Face::BOTTOM);
						mesh->UpdateNormals(Face::BOTTOM);
						mesh->UpdateTexels(blockID, Face::BOTTOM);
					}
				}
				currentBlock++;
			}
		}
		currentBlock += WorldSettings::CHUNKHEIGHT * 2;
	}
	//*ready = true;
}

void Chunk::Render(Shader shader) {
	if (ready) {
		mesh->Render(shader, Position);
		if (!updated) {
			mesh->CreateBuffer();
			updated = true;
		}
	}
}