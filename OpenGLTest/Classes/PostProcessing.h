#pragma once
//------ C++ Standard Libraries ------------//
#include <vector>
#include <iostream>
//------ GLFW, GLM and GLAD ----------------//
#include <glm/glm.hpp>
//------ Classes ---------------------------//
#include "Shader.h"
#include "..\Resources\Properties\Environment.h"

namespace PostProcessing {
    unsigned int skyboxVAO, skyboxVBO;

	void Start() {
        glGenVertexArrays(1, &skyboxVAO);
        glGenBuffers(1, &skyboxVBO);
        glBindVertexArray(skyboxVAO);
        glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
        glBufferData(GL_ARRAY_BUFFER, Environment::SKYBOXVERTICES.size() * sizeof(float), &Environment::SKYBOXVERTICES[0], GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	}

	void Render(Shader shader) {
        glDepthFunc(GL_LEQUAL);       
        glBindVertexArray(skyboxVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        glDepthFunc(GL_LESS);
	}
}