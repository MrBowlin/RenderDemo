#include "Chunk.h"

void Chunk::Start() {
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
	
	for (unsigned int x = 0; x < WIDTH; x++) {
		for (unsigned int z = 0; z < WIDTH; z++) {
			for (unsigned int y = 0; y < HEIGHT; y++) {
				glm::vec3 localPos(x, y, z);
				glm::vec3 globalPos = localPos + Position;
				int blockID = blockState[x + 1][y][z + 1];
				if (blockID > 0) {
					if (blockState[x + 1][y][z] == 0) {
						mesh.UpdatePositions(x, y, z, Face::FRONT);
						mesh.UpdateNormals(Face::FRONT);
						mesh.UpdateTexels(blockID, Face::FRONT);
					}
					if (blockState[x + 1][y][z + 2] == 0) {
						mesh.UpdatePositions(x, y, z, Face::BACK);
						mesh.UpdateNormals(Face::BACK);
						mesh.UpdateTexels(blockID, Face::BACK);
					}
					if (blockState[x][y][z + 1] == 0) {
						mesh.UpdatePositions(x, y, z, Face::LEFT);
						mesh.UpdateNormals(Face::LEFT);
						mesh.UpdateTexels(blockID, Face::LEFT);
					}
					if (blockState[x + 2][y][z + 1] == 0) {
						mesh.UpdatePositions(x, y, z, Face::RIGHT);
						mesh.UpdateNormals(Face::RIGHT);
						mesh.UpdateTexels(blockID, Face::RIGHT);
					}
					if (y == HEIGHT - 1 || blockState[x + 1][y + 1][z + 1] == 0) {
						mesh.UpdatePositions(x, y, z, Face::TOP);
						mesh.UpdateNormals(Face::TOP);
						mesh.UpdateTexels(blockID, Face::TOP);
					}
					if (y == 0 || blockState[x + 1][y - 1][z + 1] == 0) {
						mesh.UpdatePositions(x, y, z, Face::BOTTOM);
						mesh.UpdateNormals(Face::BOTTOM);
						mesh.UpdateTexels(blockID, Face::BOTTOM);
					}
				}
			}
		}
	}

	mesh.CreateBuffer();
}

void Chunk::Render(Shader shader) {
	mesh.Render(shader, Position);
}