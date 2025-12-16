#include "Camera.h"
//------ C++ Standard Libraries ------------//
//------ GLFW, GLM and GLAD ----------------//
#include <glm/gtc/matrix_transform.hpp>
//------ Classes ---------------------------//

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

glm::mat4 Camera::GetViewMatrix() {
		return glm::lookAt(Position, Position + Forward, Up);
}

void Camera::Move(glm::vec3 direction) {
	glm::vec3 flatForward = glm::cross(WorldUp, Right);
	Position += direction.x * Right + direction.y * WorldUp + direction.z * flatForward;
}

void Camera::ProcessMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch) {
	xOffset *= MouseSensitivity;
	yOffset *= MouseSensitivity;

	Yaw += xOffset;
	Pitch += yOffset;

	if (constrainPitch) {
		if (Pitch > 89.0f)
			Pitch = 89.0f;
		if (Pitch < -89.0f)
			Pitch = -89.0f;
	}

	UpdateCameraVectors();
}

void Camera::UpdateCameraVectors() {
	glm::vec3 forward;
	forward.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	forward.y = sin(glm::radians(Pitch));
	forward.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	Forward = glm::normalize(forward);
	Right = glm::normalize(glm::cross(Forward, WorldUp));
	Up = glm::normalize(glm::cross(Right, Forward));
}