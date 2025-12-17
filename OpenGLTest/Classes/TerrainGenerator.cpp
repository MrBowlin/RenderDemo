#include "TerrainGenerator.h"
//------ C++ Standard Libraries ------------//
//------ GLFW, GLM and GLAD ----------------//
//------ Classes ---------------------------//
#include "..\Includes\PerlinNoise.hpp"

TerrainGenerator2D::TerrainGenerator2D(double amplitude, double frequency, int heightOffset, long octaves, double persistance, unsigned int seed) {
	Frequency = frequency;
	Amplitude = amplitude;
	Seed = seed;
	HeightOffset = heightOffset;
	Octaves = octaves;
	Persistance = persistance;
}

int TerrainGenerator2D::HeightNoise(int x, int y) {
	siv::PerlinNoise::seed_type perlinSeed = Seed;
	siv::PerlinNoise perlin{ perlinSeed };

	double noise = perlin.octave2D_01(x * Frequency, y * Frequency, Octaves, Persistance);

	return static_cast<int>(floor(noise * Amplitude));
}

unsigned short TerrainGenerator2D::GetBlockNoise(int x, int y, int z) {
	int height = HeightNoise(x, z) + HeightOffset;
	if (y + 3 < height)		// Four Blocks below Air => Stone
		return 2;
	else if (y < height)	// Dirt
		return 1;
	else if (y == height)	// One Block below Air => Grass
		return 3;
	else					// Air
		return 0;
}

TerrainGenerator3D::TerrainGenerator3D(double density, double frequency, long octaves, double persistance, unsigned int seed) {
	Frequency = frequency;
	Density = density;
	Seed = seed;
	Octaves = octaves;
	Persistance = persistance;
}

double TerrainGenerator3D::DensityNoise(int x, int y, int z) {
	siv::PerlinNoise::seed_type perlinSeed = Seed;
	siv::PerlinNoise perlin{ perlinSeed };

	double noise = perlin.octave3D_01(x * Frequency, y * Frequency, z * Frequency, Octaves, Persistance);

	return noise * Density;
}

unsigned short TerrainGenerator3D::GetBlockNoise(int x, int y, int z) {
	double density = DensityNoise(x, y, z);
	if (density > 0.5)
		return 2;
	else				
		return 0;
}