#pragma once
//------ C++ Standard Libraries ------------//
//------ GLFW, GLM and GLAD ----------------//
#include <glad/glad.h>
#include <glm/glm.hpp>
//------ Classes ---------------------------//

// Camera-Settings
extern const float YAW;
extern const float PITCH;
extern const float SPEED;
extern const float SENSITIVITY;
extern const float ZOOM;

class Camera {
public:
	// Camera-Attributes
	glm::vec3 Position;
	glm::vec3 Forward;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;
	float Yaw;
	float Pitch;
	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;

	float lastX = 0.0f;
	float lastY = 0.0f;
	bool firstMouse = true;

	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
		float yaw = YAW, float pitch = PITCH) :
		Forward(glm::vec3(0.0f, 0.0f, -1.0f)),
		MovementSpeed(SPEED),
		MouseSensitivity(SENSITIVITY),
		Zoom(ZOOM)
	{
		Position = position;
		WorldUp = up;
		Yaw = yaw;
		Pitch = pitch;
		UpdateCameraVectors();
	}

	Camera(float posX, float posY, float posZ,
		float upX, float upY, float upZ, float yaw,
		float pitch) :
		Forward(glm::vec3(0.0f, 0.0f, -1.0f)),
		MovementSpeed(SPEED),
		MouseSensitivity(SENSITIVITY),
		Zoom(ZOOM)
	{
		Position = glm::vec3(posX, posY, posZ);
		WorldUp = glm::vec3(upX, upY, upZ);
		Yaw = yaw;
		Pitch = pitch;
		UpdateCameraVectors();
	}

	glm::mat4 GetViewMatrix();

	void Move(glm::vec3 direction);

	void ProcessMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch = true);

private:
	void UpdateCameraVectors();
};