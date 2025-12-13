#pragma once

class TerrainGenerator2D {

	// Settings
	float Frequency;
	float Amplitude;
	unsigned int Seed;
	unsigned int HeightOffset;

public:

	class TerrainGenerator2D(float amplitude = 1.0f, float frequency = 1.0f, unsigned int heightOffset = 0, unsigned int seed = 123456) {
		Frequency = frequency;
		Amplitude = amplitude;
		Seed = seed;
		HeightOffset = heightOffset;
	}

	unsigned int HeightNoise(unsigned int x, unsigned int y);

	bool IsBlockNoise(unsigned int x, unsigned int y, unsigned int z);

	unsigned int GetBlockNoise(unsigned int x, unsigned int y, unsigned int z);
};

class TerrainGenerator3D {

	// Settings
	float Frequency;
	float Density;
	float Threshhold;
	unsigned int Seed;

public: 
	class TerrainGenerator3D(float density = 1.0f, float frequency = 1.0f, float threshhold = 0.5f, unsigned int seed = 123456) {
		Frequency = frequency;
		Density = density;
		Seed = seed;
		Threshhold = threshhold;
	}

	float DensityNoise(unsigned int x, unsigned int y, unsigned int z);

	bool IsBlockNoise(unsigned int x, unsigned int y, unsigned int z);

	unsigned int GetBlockNoise(unsigned int x, unsigned int y, unsigned int z);
};