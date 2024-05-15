#include "Airplane.h"

Airplane::Airplane() :
	Model("models/plane/scene.gltf")
{
	//glm::vec3(-155.995f, 125.023f, 29.9496f) // no view
	// glm::vec3(-100.495f, 29.023f, -18.0504f) // no view close

	//no view
	//SetTransformations(glm::vec3(603.f, -1809.f, -23014.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(5.1f, 5.1f, 5.1f), glm::radians(90.f));

	//glm::vec3(585.005f, 1590.52f, -456.05f), // view  
	// glm::vec3(163.0f, -1171.0f, 174.55f); // rotation view
	//view
	//SetTransformations(glm::vec3(119907.f, 1893.52f, -127622.f), glm::vec3(0.f, -1.f, 0.f), glm::vec3(5.1f, 5.1f, 5.1f), glm::radians(90.f));



	//-104.995 35.023 - 9.0504
}

void Airplane::Inputs(GLFWwindow* window)
{
	glm::mat4 rotation = glm::mat4(1.0f);
	rotation *= kBaseRotation;

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		rotation *= kUpRotation;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		rotation *= kDownRotation;
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		rotation *= kRightRotation;
	}
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		rotation *= kLeftRotation;
	}
	SetTransformations(kNoViewTranslation, kScale, rotation);
}

void Airplane::NoViewDraw(Shader& shader, Camera& camera)
{
	Model::NoViewDraw(shader, camera);
}

void Airplane::Draw(Shader& shader, Camera& camera)
{
	glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(90.f), glm::vec3(0.f, -1.f, 0.f));
	SetTransformations(glm::vec3(119907.f, 1893.52f, -127622.f), kScale, rotation);
	Model::Draw(shader, camera);
}

void Airplane::Draw(Shader& shader, Camera& camera, bool attached)
{
	if (attached)
		Airplane::NoViewDraw(shader, camera);
	else
		Airplane::Draw(shader, camera);
}
