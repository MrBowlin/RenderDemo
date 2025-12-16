#include "TerrainGenerator.h"
//------ C++ Standard Libraries ------------//
//------ GLFW, GLM and GLAD ----------------//
//------ Classes ---------------------------//
#include "..\Includes\PerlinNoise.hpp"

TerrainGenerator2D::TerrainGenerator2D(float amplitude, float frequency, int heightOffset, unsigned int seed) {
	Frequency = frequency;
	Amplitude = amplitude;
	Seed = seed;
	HeightOffset = heightOffset;
}

unsigned int TerrainGenerator2D::HeightNoise(int x, int y) {
	siv::PerlinNoise::seed_type perlinSeed = Seed;
	siv::PerlinNoise perlin{ perlinSeed };

	float noise = static_cast<float>(perlin.noise2D_01(static_cast<double>(x * Frequency), static_cast<double>(y * Frequency)));

	return static_cast<unsigned int>(floor(noise * Amplitude));
}

bool TerrainGenerator2D::IsBlockNoise(int x, int y, int z) {
	int height = static_cast<int>(HeightNoise(x, z) + HeightOffset);
	return y <= height;
}

unsigned int TerrainGenerator2D::GetBlockNoise(int x, int y, int z) {
	int height = static_cast<int>(HeightNoise(x, z) + HeightOffset);
	if (y + 3 < height)		// Four Blocks below Air => Stone
		return 2;
	else if (y < height)	// Dirt
		return 1;
	else if (y == height)	// One Block below Air => Grass
		return 3;
	else					// Air
		return 0;
}

TerrainGenerator3D::TerrainGenerator3D(float density, float frequency, float threshhold, unsigned int seed) {
	Frequency = frequency;
	Density = density;
	Seed = seed;
	Threshhold = threshhold;
}

float TerrainGenerator3D::DensityNoise(int x, int y, int z) {
	siv::PerlinNoise::seed_type perlinSeed = Seed;
	siv::PerlinNoise perlin{ perlinSeed };

	float noise = static_cast<float>(perlin.noise3D_01(static_cast<double>(x * Frequency), static_cast<double>(y * Frequency), static_cast<double>(z * Frequency)));

	return static_cast<float>(noise * Density);
}

bool TerrainGenerator3D::IsBlockNoise(int x, int y, int z) {
	return DensityNoise(x, y, z) > Threshhold;
}

unsigned int TerrainGenerator3D::GetBlockNoise(int x, int y, int z) {
	float density = DensityNoise(x, y, z);
	if (density > Threshhold)
		return 2;
	else				
		return 0;
}