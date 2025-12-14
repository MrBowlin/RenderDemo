#pragma once

class TerrainGenerator2D {

	// Settings
	float Frequency;
	float Amplitude;
	unsigned int Seed;
	unsigned int HeightOffset;

public:

	class TerrainGenerator2D(float amplitude = 1.0f, float frequency = 1.0f, int heightOffset = 0, unsigned int seed = 123456) {
		Frequency = frequency;
		Amplitude = amplitude;
		Seed = seed;
		HeightOffset = heightOffset;
	}

	unsigned int HeightNoise(int x, int y);

	bool IsBlockNoise(int x, int y, int z);

	unsigned int GetBlockNoise(int x, int y, int z);
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

	float DensityNoise(int x, int y, int z);

	bool IsBlockNoise(int x, int y, int z);

	unsigned int GetBlockNoise(int x, int y, int z);
};