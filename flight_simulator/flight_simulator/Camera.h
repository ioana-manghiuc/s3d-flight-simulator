#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include <GL/glew.h>
#include <glfw3.h>

#include <GLM.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include<gtx/rotate_vector.hpp>
#include<gtx/vector_angle.hpp>

#include "Shader.h"

class Camera
{
public:
	glm::vec3 Position;
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 cameraMatrix = glm::mat4(1.0f);

	bool firstClick = true;

	int width;
	int height;

	float speed = 0.001f;
	float sensitivity = 100.0f;

	// Camera constructor to set up initial values
	Camera(int width, int height, glm::vec3 position);

	// Updates the camera matrix to the Vertex Shader
	void updateMatrix(float FOVdeg, float nearPlane, float farPlane);

	// Exports the camera matrix to a shader
	void Matrix(Shader& shader, const char* uniform);

	// Handles camera inputs
	void Inputs(GLFWwindow* window);
};
#endif