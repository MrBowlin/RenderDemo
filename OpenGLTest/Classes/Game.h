#pragma once
//------ C++ Standard Libraries ------------//
//------ GLFW, GLM and GLAD ----------------//
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
//------ Classes ---------------------------//
#include "Shader.h"
#include "Camera.h"
#include "World.h"

namespace Game {

	extern Camera mainCamera;
	extern World world;

	extern glm::vec3 lightColor;
	extern glm::vec3 lightDirection;
	extern float ambientStrength;

	/**
	 * This function is called once after the Initialization of GLFW and GLAD was completed.
	 * @param -
	 * @return void
	 */	
	void Start();

	/**
	 * This function is called once per Frame to before the Update-function is called.
	 * It is supposed to handle all Keyboard-Input for the Game.
	 * @param GLFWwindow* window: Pointer to the GLFW-Window currently in use.
	 * @param float deltaTime: Time since the last call of Update. 
	 * @return void
	 */
	void ProcessInput(GLFWwindow* window, float deltaTime);

	/**
	 * This function is called once per Frame to before the Update-function is called.
	 * It is supposed to handle all Mouse-Input for the Game.
	 * @param GLFWwindow* window: Pointer to the GLFW-Window currently in use.
	 * @param double xposIn: Current X-Position of the Mouse in Screen-Space.
	 * @param double yposIn: Current Y-Position of the Mouse in Screen-Space.
	 * @return void
	 */
	void MouseCallback(GLFWwindow* window, double xposIn, double yposIn);

	/**
	 * This function is called once per Frame before the Render-function is called. 
	 * It is supposed to handle physics and In-Game logik that take place before Rendering.
	 * @param float deltaTime: Time since the last call of Update. 
	 * @return void
	 */
	void Update(float deltaTime);

	/**
	* This function is called once per Frame after the Update-function was called.
	* It is supposed to handle all Rendering of the Game.
	* @param Shader shader: Current active base Shader for Rendering.
	* @param int screenWidth: Current width of the Screen in Pixels.
	* @param int screenHeight: Current height of the Screen in Pixels.
	* @return void
	*/
	void Render(Shader shader, int screenWidth, int screenHeight);

	/**
	 * This function is called once per Frame after the Render-function is called.
	 * It is supposed to handle physics and In-Game logik that take place after Rendering.
	 * @param float deltaTime: Time since the last call of LastUpdate.
	 * @return void
	 */
	void LateUpdate(float deltaTime);
};