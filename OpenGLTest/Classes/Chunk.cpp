#include "Chunk.h"
#include "World.h"
#include <thread>

void Chunk::Start() {
	std::thread meshThread(Chunk::UpdateMesh, &terrain2d, &terrain3d, &blockStates, mesh, &ready, Position.x, Position.z);
	meshThread.detach();
}

void Chunk::UpdateMesh(TerrainGenerator2D *terrain2d, TerrainGenerator3D *terrain3d, std::vector<uint8_t>* blockStates, Mesh *mesh, bool* ready, int xPos, int zPos) {
	for (int x = 0; x < CHUNKWIDTH; x++) {
		for (int z = 0; z < CHUNKWIDTH; z++) {
			for (int y = 0; y < CHUNKHEIGHT; y++) {
				if (terrain3d->GetBlockNoise(static_cast<int>(xPos) + x - 1, y, static_cast<int>(zPos) + z - 1) == 0) {
					blockStates->push_back(0);
				}
				else {
					blockStates->push_back(terrain2d->GetBlockNoise(static_cast<int>(xPos) + x - 1, y, static_cast<int>(zPos) + z - 1));
				}
			}
		}
	}

	for (unsigned int x = 1; x < CHUNKWIDTH - 1; x++) {
		for (unsigned int z = 1; z < CHUNKWIDTH - 1; z++) {
			for (unsigned int y = 0; y < CHUNKHEIGHT; y++) {
				unsigned int currentBlock = x * CHUNKHEIGHT * CHUNKWIDTH + z * CHUNKHEIGHT + y;
				int blockID = blockStates->at(currentBlock);
				if (blockID > 0) {
					if (blockStates->at(currentBlock- CHUNKHEIGHT) == 0) {
						mesh->UpdatePositions(x - 1, y, z - 1, Face::FRONT);
						mesh->UpdateNormals(Face::FRONT);
						mesh->UpdateTexels(blockID, Face::FRONT);
					}
					if (blockStates->at(currentBlock + CHUNKHEIGHT) == 0) {
						mesh->UpdatePositions(x - 1, y, z - 1, Face::BACK);
						mesh->UpdateNormals(Face::BACK);
						mesh->UpdateTexels(blockID, Face::BACK);
					}
					if (blockStates->at(currentBlock - CHUNKHEIGHT * CHUNKWIDTH) == 0) {
						mesh->UpdatePositions(x - 1, y, z - 1, Face::LEFT);
						mesh->UpdateNormals(Face::LEFT);
						mesh->UpdateTexels(blockID, Face::LEFT);
					}
					if (blockStates->at(currentBlock + CHUNKHEIGHT * CHUNKWIDTH) == 0) {
						mesh->UpdatePositions(x - 1, y, z - 1, Face::RIGHT);
						mesh->UpdateNormals(Face::RIGHT);
						mesh->UpdateTexels(blockID, Face::RIGHT);
					}
					if (y == CHUNKHEIGHT - 1 || blockStates->at(currentBlock + 1) == 0) {
						mesh->UpdatePositions(x - 1, y, z - 1, Face::TOP);
						mesh->UpdateNormals(Face::TOP);
						mesh->UpdateTexels(blockID, Face::TOP);
					}
					if (y == 0 || blockStates->at(currentBlock - 1) == 0) {
						mesh->UpdatePositions(x - 1, y, z - 1, Face::BOTTOM);
						mesh->UpdateNormals(Face::BOTTOM);
						mesh->UpdateTexels(blockID, Face::BOTTOM);
					}
				}
			}
		}
	}
	*ready = true;
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