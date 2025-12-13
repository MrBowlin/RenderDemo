#include "TerrainGenerator.h"
#include <cmath>
#include <iostream>
#include "..\PerlinNoise.hpp"

unsigned int TerrainGenerator2D::HeightNoise(unsigned int x, unsigned int y) {
	siv::PerlinNoise::seed_type perlinSeed = Seed;
	siv::PerlinNoise perlin{ perlinSeed };

	float noise = static_cast<float>(perlin.noise2D_01(static_cast<double>(x * Frequency), static_cast<double>(y * Frequency)));

	return static_cast<unsigned int>(floor(noise * Amplitude));
}

bool TerrainGenerator2D::IsBlockNoise(unsigned int x, unsigned int y, unsigned int z) {
	unsigned int height = HeightNoise(x, z) + HeightOffset;
	return y <= height;
}

unsigned int TerrainGenerator2D::GetBlockNoise(unsigned int x, unsigned int y, unsigned int z) {
	unsigned int height = HeightNoise(x, z) + HeightOffset;
	if (y + 3 < height)		// Four Blocks below Air => Stone
		return 2;
	else if (y < height)	// Dirt
		return 1;
	else if (y == height)	// One Block below Air => Grass
		return 3;
	else					// Air
		return 0;
}

float TerrainGenerator3D::DensityNoise(unsigned int x, unsigned int y, unsigned int z) {
	siv::PerlinNoise::seed_type perlinSeed = Seed;
	siv::PerlinNoise perlin{ perlinSeed };

	float noise = static_cast<float>(perlin.noise3D_01(static_cast<double>(x * Frequency), static_cast<double>(y * Frequency), static_cast<double>(z * Frequency)));

	return static_cast<float>(noise * Density);
}

bool TerrainGenerator3D::IsBlockNoise(unsigned int x, unsigned int y, unsigned int z) {
	return DensityNoise(x, y, z) > Threshhold;
}

unsigned int TerrainGenerator3D::GetBlockNoise(unsigned int x, unsigned int y, unsigned int z) {
	float density = DensityNoise(x, y, z);
	if (density > Threshhold)
		return 2;
	else				
		return 0;
}