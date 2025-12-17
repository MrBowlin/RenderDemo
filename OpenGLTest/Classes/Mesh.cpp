#include "Mesh.h"
//------ C++ Standard Libraries ------------//
//------ GLFW, GLM and GLAD ----------------//
#include <glm/gtc/type_ptr.hpp>
//------ Classes ---------------------------//
#include "..\Ressources\Properties\BlockData.h"

Mesh::Mesh() {
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	triangleCount = 0;
}

Mesh::~Mesh() {
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
}

void Mesh::CreateBuffer() {
	if (positions.size() == 0)
		return;

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER,
		positions.size() * sizeof(float) +
		texels.size() * sizeof(float) +
		normals.size() * sizeof(float), 0, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0,
		positions.size() * sizeof(float), &positions.front());
	glBufferSubData(GL_ARRAY_BUFFER,
		positions.size() * sizeof(float),
		texels.size() * sizeof(float), &texels.front());
	glBufferSubData(GL_ARRAY_BUFFER,
		positions.size() * sizeof(float) +
		texels.size() * sizeof(float),
		normals.size() * sizeof(float), &normals.front());

	// Buffer-Concept: (PosX PosY PosZ)* (TexX TexY)* (NorX NorY NorZ)*

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(positions.size() * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(positions.size() * sizeof(float) + texels.size() * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);

	triangleCount = static_cast<unsigned int>(floor(positions.size() / 3));
}

void Mesh::Render(Shader shader, glm::vec3 position) {
	shader.setInt("texture", 0);
	glBindVertexArray(VAO);
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, position);
	shader.setMat4("model", model);
	glDrawArrays(GL_TRIANGLES, 0, triangleCount);
}

void Mesh::UpdatePositions(unsigned int x, unsigned int y, unsigned int z, Face face) {
	const std::vector<float>* indices;
	switch (face)
	{
	case Face::TOP:
		indices = &BlockData::TOPVERTICES;
		break;
	case Face::BOTTOM:
		indices = &BlockData::BOTTOMVERTICES;
		break;
	case Face::FRONT:
		indices = &BlockData::FRONTVERTICES;
		break;
	case Face::BACK:
		indices = &BlockData::BACKVERTICES;
		break;
	case Face::LEFT:
		indices = &BlockData::LEFTVERTICES;
		break;
	case Face::RIGHT:
		indices = &BlockData::RIGHTVERTICES;
		break;
	default:
		std::cout << "Tried to create Positions but invalid Face-Type" << std::endl;
		return;
	}
	for (unsigned int i = 0; i < 6 * 3; i += 3) {
		positions.push_back(x + indices->at(i));
		positions.push_back(y + indices->at(i + 1));
		positions.push_back(z + indices->at(i + 2));
	}
}

void Mesh::UpdateNormals(Face face) {
	const std::vector<float>* indices;
	switch (face)
	{
	case Face::TOP:
		indices = &BlockData::TOPNORMALS;
		break;
	case Face::BOTTOM:
		indices = &BlockData::BOTTOMNORMALS;
		break;
	case Face::FRONT:
		indices = &BlockData::FRONTNORMALS;
		break;
	case Face::BACK:
		indices = &BlockData::BOTTOMNORMALS;
		break;
	case Face::LEFT:
		indices = &BlockData::LEFTNORMALS;
		break;
	case Face::RIGHT:
		indices = &BlockData::RIGHTNORMALS;
		break;
	default:
		std::cout << "Tried to create Normals but invalid Face-Type" << std::endl;
		return;
	}
	for (unsigned int i = 0; i < 6; i++) {
		normals.push_back(indices->at(0));
		normals.push_back(indices->at(1));
		normals.push_back(indices->at(2));
	}
}

void Mesh::UpdateTexels(unsigned int blockID, Face face) {
	float xOffset;
	float yOffset;
	GetOffset(blockID, face, &xOffset, &yOffset);

	const std::vector<float>* indices = &BlockData::COMMONTEXELS;
	for (unsigned int i = 0; i < 6 * 2; i += 2) {
		texels.push_back((indices->at(i) + xOffset) / 16.0f);
		texels.push_back((indices->at(i + 1) + 15 - yOffset) / 16.0f);
	}
}

void Mesh::GetOffset(unsigned int blockID, Face face, float* xOffset, float* yOffset) {
	int textureID;
	switch (blockID)
	{
	case 1:		// Dirt
		textureID = 3;
		break;
	case 2:		// Stone
		textureID = 2;
		break;
	case 3:		// Grass
		if (face == Face::TOP)
			textureID = 1;
		else if (face == Face::BOTTOM)
			textureID = 3;
		else
			textureID = 4;
		break;
	case 4:		// Cobblestone
		textureID = 17;
		break;
	case 5:		// Log
		if (face == Face::TOP || face == Face::BOTTOM)
			textureID = 22;
		else
			textureID = 21;
		break;
	case 6:		// Sand
		textureID = 19;
		break;
	case 7:		// Planks
		textureID = 5;
		break;
	default:
		*xOffset = 10.0f;
		*yOffset = 14.0f;
		return;
	}
	*xOffset = BlockData::TEXTURECOORDINATES.at(textureID * 2 - 2);
	*yOffset = BlockData::TEXTURECOORDINATES.at(textureID * 2 - 1);
	return;
}