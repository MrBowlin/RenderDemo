#pragma once
//------ C++ Standard Libraries ------------//
//------ GLFW, GLM and GLAD ----------------//
//------ Classes ---------------------------//

class TerrainGenerator2D {

	// Settings
	double Frequency;
	double Amplitude;
	long Octaves;
	double Persistance;
	unsigned int Seed;
	unsigned int HeightOffset;

public:

	TerrainGenerator2D(double amplitude = 1, double frequency = 1, int heightOffset = 0, long octaves = 1, double persistance = 0.5, unsigned int seed = 123456);

	int HeightNoise(int x, int y);

	unsigned short GetBlockNoise(int x, int y, int z);
};

class TerrainGenerator3D {

	// Settings
	double Frequency;
	double Density;
	long Octaves;
	double Persistance;
	unsigned int Seed;

public: 
	TerrainGenerator3D(double density = 1, double frequency = 1, long octaves = 1, double persistance = 0.5, unsigned int seed = 123456);

	double DensityNoise(int x, int y, int z);

	unsigned short GetBlockNoise(int x, int y, int z);
};