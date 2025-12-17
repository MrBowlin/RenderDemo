#include "TerrainGenerator.h"
//------ C++ Standard Libraries ------------//
#include <iostream>
//------ GLFW, GLM and GLAD ----------------//
//------ Classes ---------------------------//
#include "..\Includes\PerlinNoise.hpp"
#include "..\Settings\WorldSettings.h"

TerrainGenerator2D::TerrainGenerator2D(
	double amplitude, 
	double frequency, 
	int heightOffset, 
	long octaves, 
	double persistance, 
	double amplifierStrength,
	unsigned int seed) 
{
	Frequency = frequency;
	Amplitude = amplitude;
	Seed = seed;
	HeightOffset = heightOffset;
	Octaves = octaves;
	Persistance = persistance;
	AmplifierStrength = amplifierStrength;
}

int TerrainGenerator2D::HeightNoise(int x, int y) {
	siv::PerlinNoise::seed_type perlinSeed = Seed;
	siv::PerlinNoise perlin{ perlinSeed };

	double noise = perlin.octave2D_01(x * Frequency, y * Frequency, Octaves, Persistance);

	double amplifiedNoise = pow(noise, AmplifierStrength);

	return static_cast<int>(amplifiedNoise * Amplitude) + HeightOffset;
}

unsigned short TerrainGenerator2D::GetBlockNoise(int x, int y, int z) {
	int height = HeightNoise(x, z);
	if (y > height)			
		return 0;			// Air

	if (y >= WorldSettings::MOUNTAINLEVEL)
		return 2;			// Mountain

	if (y <= WorldSettings::WATERTLEVEL)
		return 6;			// Sand

	if (y + 3 < height)		
		return 2;			// Four Blocks below Air => Stone

	if (y < height)	
		return 1;			// Dirt

	if (y == height)	
		return 3;			// One Block below Air => Grass

	return 0;				// Fallback
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

	return 0;
}