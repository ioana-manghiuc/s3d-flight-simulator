#pragma once
#include "ECameraMovementType.h"

#pragma once

#include <vec3.hpp>
#include <mat4x4.hpp>

#include <GL/glew.h>

const float SPEED = 7.0f;

class Camera
{

private:

	const float zNEAR = 0.1f;
	const float zFAR = 1000.f;
	const float YAW = -90.0f;
	const float PITCH = 0.0f;
	const float FOV = 45.0f;


public:

	glm::vec3 startPosition;
	glm::vec3 position;

	Camera(const int width, const int height, const glm::vec3& position);

	void Set(const int width, const int height, const glm::vec3& position);

	void Reset(const int width, const int height);
	void Reshape(int windowWidth, int windowHeight);

	const glm::mat4 GetViewMatrix() const;
	const glm::vec3 GetPosition() const;
	const glm::mat4 GetProjectionMatrix() const;

	void ProcessKeyboard(ECameraMovementType direction, float deltaTime);
	void MouseControl(float xPos, float yPos);
	void ProcessMouseScroll(float yOffset);

	void ProcessMouseMovement(float xOffset, float yOffset, bool constrainPitch = true);

private:

	void UpdateCameraVectors();

protected:

	const float cameraSpeedFactor = 2.5f;
	const float mouseSensitivity = 0.1f;

	float zNear;
	float zFar;
	float FoVy;
	int width;
	int height;
	bool isPerspective;

	glm::vec3 forward;
	glm::vec3 right;
	glm::vec3 up;
	glm::vec3 worldUp;

	float yaw;
	float pitch;

	bool bFirstMouseMove = true;
	float lastX = 0.f, lastY = 0.f;
};

