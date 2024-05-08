#include "Airplane.h"

Airplane::Airplane():
	model{ "models/plane/scene.gltf" }
{
	/*model.translation = glm::vec3(-1185.9, 1386.8, 766.6);
	model.rotation = glm::vec3(163.0f, -1171.0f, 174.55f);
	model.scale = glm::vec3(0.1f, 0.1f, 0.1f);*/

	model.translation = glm::vec3(-95.9f, 400.0f, 50.0f);
	model.rotation = glm::vec3(163.0f, -1171.0f, 174.55f);
	model.scale = glm::vec3(0.1f, 0.1f, 0.1f);
	
}

void Airplane::Draw(Shader& shader, Camera& camera)
{
	model.Draw(shader, camera);
}

void Airplane::Inputs(GLFWwindow* window)
{
	// only one active at a time

	model.Translation(window);
	//model.Rotation(window);
}