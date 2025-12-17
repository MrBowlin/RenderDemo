#pragma once

namespace WorldSettings {

	// World-Settings
	const unsigned int CHUNKWIDTH = 18;
	const unsigned int CHUNKHEIGHT = 64;

	const unsigned int WORLDSIZE = 256;

	const unsigned int CHUNKCOUNT = 16;

	// Terrain-Generation-Settings
	const int HEIGHTOFFSET = 8;
	const int MOUNTAINLEVEL = 28;
	const int WATERTLEVEL = 12;

	const double CAVENOISEFREQUENCY = 0.01;
	const double CAVENOISEDENSITY = 10;
	const long CAVENOISEOCTAVES = 1;
	const double CAVENOISEPERSISTANCE = 0.5;

	const double WORLDNOISEFREQUENCY = 0.005;
	const double WORLDNOISEAMPLITUDE = 100.0;
	const long WORLDNOISEOCTAVES = 3;
	const double WORLDNOISEPERSISTANCE = 0.75;

	const double AMPLIFIERSTRENGTH = 3;
}
