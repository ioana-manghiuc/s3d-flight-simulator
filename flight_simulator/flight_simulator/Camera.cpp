#include "Camera.h"
#include "PositionValidations.h"
Camera::Camera(int width, int height)
{
	Camera::width = width;
	Camera::height = height;
	Position = kBasePosition;
	//Position = kOrigin;
	Orientation = kBaseOrientation;
    //PlanePosition = position;
}

void Camera::UpdateMatrix(float FOVdeg, float nearPlane, float farPlane)
{
	// Initializes matrices since otherwise they will be the null matrix
	glm::mat4 view = glm::mat4(1.0f);

	// Makes camera look in the right direction from the right position
	view = glm::lookAt(Position, Position + Orientation, Up);
	// Adds perspective to the scene
	projection = glm::perspective(glm::radians(FOVdeg), (float)width / height, nearPlane, farPlane);

	// Sets new camera matrix
	cameraMatrix = projection * view;
}

void Camera::Matrix(Shader& shader, const char* uniform)
{
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
}

void Camera::NoViewMatrix(Shader& shader, const char* uniform)
{
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(projection));
}

void Camera::ProcessMouseScroll(float yOffset)
{
	float scrollSpeed = 1.0f;
	Position += static_cast<float>(yOffset) * scrollSpeed * Orientation;
}

void Camera::Inputs(GLFWwindow* window)
{
	LastPosition = Position;

	// Handles key inputs

	if (isPlaneAttached)
		AttachedInputs(window);
	else
		DetachedInputs(window);

	//std::cout << Position.x << " " << Position.y << " " << Position.z << '\n';
}

void Camera::AttachedInputs(GLFWwindow* window)
{
	Position += speed * Orientation;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		if (speed <= 2 * kFastSpeed)
			speed += 0.01;
	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		speed -= 0.01;
		if (speed < 0.0)
			speed = 0;
	}
	glm::vec3 planePosition = Position + 100.f * Orientation;
	if (!IsValidPosition(planePosition))
	{
		Position = LastPosition;
		hasCollided = true;
	}

	float leftRightSensitivity = 0.25;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		ChangeOrientation(0.0, -leftRightSensitivity);
	}
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		ChangeOrientation(0.0, leftRightSensitivity);
	}
	if (speed < 0.5)
		return;

	float upDownSensitivity = 0.3;
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		ChangeOrientation(-upDownSensitivity, 0.0);
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		ChangeOrientation(upDownSensitivity, 0.0);
	}
}

void Camera::DetachedInputs(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		Position += speed * Orientation;

		std::cout << Position.x << ", " << Position.y << ", " << Position.z << '\n';
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		Position += speed * -Orientation;
		std::cout << Position.x << ", " << Position.y << ", " << Position.z << '\n';
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		speed = kFastSpeed;
		std::cout << Position.x << ", " << Position.y << ", " << Position.z << '\n';
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
		speed = kSlowSpeed;
		std::cout << Position.x << ", " << Position.y << ", " << Position.z << '\n';
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		Position += speed * Up;
		std::cout << Position.x << ", " << Position.y << ", " << Position.z << '\n';
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		Position += speed * -Up;
		std::cout << Position.x << ", " << Position.y << ", " << Position.z << '\n';
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		Position += speed * -glm::normalize(glm::cross(Orientation, Up));
		std::cout << Position.x << ", " << Position.y << ", " << Position.z << '\n';
	}
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		Position += speed * glm::normalize(glm::cross(Orientation, Up));
		std::cout << Position.x << ", " << Position.y << ", " << Position.z << '\n';
	}
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		if (firstClick)
		{
			glfwSetCursorPos(window, (width / 2), (height / 2));
			firstClick = false;
		}

		double mouseX;
		double mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);

		float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
		float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;

		ChangeOrientation(rotX, rotY);

		//std::cout << "orientation: " << Orientation.x << " " << Orientation.y << " " << Orientation.z << "\n";

		glfwSetCursorPos(window, (width / 2), (height / 2));
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		firstClick = true;
	}
}

void Camera::ChangeOrientation(float rotX, float rotY)
{
	glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));

	if (abs(glm::angle(newOrientation, Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
	{
		Orientation = newOrientation;
	}

	Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);
}

void Camera::SetIsAttached(bool isAttached)
{
	if (this->isPlaneAttached == isAttached)
		return;

	//Position = kBasePosition;
	//Orientation = kBaseOrientation;
	Position = kStartFlightPos;
	Orientation = kStartFlightOrientation;

	this->isPlaneAttached = isAttached;
	if (isAttached)
		speed = 0.0f;
	else
	{
		speed = kSlowSpeed;
		hasCollided = false;
	}

}

