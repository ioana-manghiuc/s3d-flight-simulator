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
	Camera(int width, int height, glm::vec3 position); // Camera constructor to set up initial values

	void UpdateMatrix(float FOVdeg, float nearPlane, float farPlane); // Updates the camera matrix to the Vertex Shader	
	void Matrix(Shader& shader, const char* uniform); // Exports the camera matrix to a shader
	void ProcessMouseScroll(float yOffset); // Processes mouse scrolling
	void Inputs(GLFWwindow* window); 	// Handles camera inputs

public:
	glm::vec3 Position;
	glm::vec3 PlanePosition = glm::vec3(-95.9f, 400.0f, 50.0f);
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 cameraMatrix = glm::mat4(1.0f);

	bool firstClick = true;

	int width;
	int height;

	float speed = 0.001f;
	float sensitivity = 100.0f;
};
#endif