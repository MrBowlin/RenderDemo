#pragma once

#include <vector>

namespace BlockData {
	const std::vector<float>TOPVERTICES = {
	1.0f, 1.0f, 1.0f,
	0.0f, 1.0f, 1.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	1.0f, 1.0f, 0.0f,
	1.0f, 1.0f, 1.0f,
	};

	const std::vector<float>TOPNORMALS = {
		0.0f, 1.0f, 0.0f,
	};

	const std::vector<float>BOTTOMVERTICES = {
		0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
	};

	const std::vector<float>BOTTOMNORMALS = {
		0.0f, -1.0f, 0.0f,
	};

	const std::vector<float>LEFTVERTICES = {
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
	};

	const std::vector<float>LEFTNORMALS = {
		-1.0f, 0.0f, 0.0f,
	};

	const std::vector<float>RIGHTVERTICES = {
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
	};

	const std::vector<float>RIGHTNORMALS = {
		1.0f, 0.0f, 0.0f,
	};

	const std::vector<float>FRONTVERTICES = {
		0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
	};

	const std::vector<float>FRONTNORMALS = {
		0.0f, 0.0f, -1.0f,
	};

	const std::vector<float>BACKVERTICES = {
		1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f,
	};

	const std::vector<float>BACKNORMALS = {
		0.0f, 0.0f, 1.0f,
	};

	const std::vector<float>COMMONTEXELS = {
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,
	};

	const std::vector<float>TEXTURECOORDINATES = {
		//xOffset yOffset
							// 0:Air
			0.0f,	0.0f,	// 1:Grass-Top
			1.0f,	0.0f,	// 2:Stone
			2.0f,	0.0f,	// 3:Dirt
			3.0f,	0.0f,	// 4:Grass-Side
			4.0f,	0.0f,	// 5:Planks
			5.0f,	0.0f,	// 6:Smooth-Stone-Side
			6.0f,	0.0f,	// 7:Smooth-Stone-Top
			7.0f,	0.0f,	// 8:Bricks
			8.0f,	0.0f,	// 9:TNT-Side
			9.0f,	0.0f,	// 10:TNT-Top
			10.0f,	0.0f,	// 11:TNT-Bottom
			11.0f,	0.0f,	// 12:Cobweb
			12.0f,	0.0f,	// 13:Flower-Red
			13.0f,	0.0f,	// 14:Flower-Yellow
			14.0f,	0.0f,	// 15:Water
			15.0f,	0.0f,	// 16:Sappling
			0.0f,	1.0f,	// 17:Cobblestone
			1.0f,	1.0f,	// 18:Bedrock
			2.0f,	1.0f,	// 19:Sand
			3.0f,	1.0f,	// 20:Gravel
			4.0f,	1.0f,	// 21:Log-Side
			5.0f,	1.0f,	// 22:Log-Top
			6.0f,	1.0f,	// 23:Iron-Block
			7.0f,	1.0f,	// 24:Gold-Block
			8.0f,	1.0f,	// 25:Diamond-Block
			9.0f,	1.0f,	// 26:Emerald-Block
			10.0f,	1.0f,	// 27:Redstone-Block
	};
}