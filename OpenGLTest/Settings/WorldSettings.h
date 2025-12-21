#pragma once

namespace WorldSettings {

	// World-Settings
	const int CHUNKWIDTH = 18;
	const int CHUNKHEIGHT = 128;

	const int WORLDSIZE = 256;

	const int CHUNKCOUNT = 8;

	// Terrain-Generation-Settings
	const int HEIGHTOFFSET = 32;
	const int MOUNTAINLEVEL = 64;
	const int WATERTLEVEL = 0;

	const double CAVENOISEFREQUENCY = 0.01;
	const double CAVENOISEDENSITY = 1.25;
	const long CAVENOISEOCTAVES = 3;
	const double CAVENOISEPERSISTANCE = 0.75;

	const double WORLDNOISEFREQUENCY = 0.005;
	const double WORLDNOISEAMPLITUDE = 50;
	const long WORLDNOISEOCTAVES = 3;
	const double WORLDNOISEPERSISTANCE = 0.75;

	const double AMPLIFIERSTRENGTH = 3;
}
