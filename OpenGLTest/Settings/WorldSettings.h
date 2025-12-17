#pragma once

namespace WorldSettings {

	// World-Settings
	const unsigned int CHUNKWIDTH = 18;
	const unsigned int CHUNKHEIGHT = 64;

	const unsigned int WORLDSIZE = 256;

	const unsigned int CHUNKCOUNT = 32;

	// Terrain-Generation-Settings
	const int HEIGHTOFFSET = 8;
	const int WATERTLEVEL = 10;

	const double CAVENOISEFREQUENCY = 0.01;
	const double CAVENOISEDENSITY = 1.5;
	const long CAVENOISEOCTAVES = 1;
	const double CAVENOISEPERSISTANCE = 0.5;

	const double WORLDNOISEFREQUENCY = 0.05;
	const double WORLDNOISEAMPLITUDE = 15.0;
	const long WORLDNOISEOCTAVES = 1;
	const double WORLDNOISEPERSISTANCE = 0.5;
}
