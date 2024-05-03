#include "Airplane.h"

Airplane::Airplane():
	model{ "models/plane/scene.gltf" }
{
	model.translation = glm::vec3(-130.0f, 371.0f, 0.0f);
	model.rotation = glm::quat(1.0f, 0.0f, -0.45f, 0.0f);
	model.scale = glm::vec3(0.1f, 0.1f, 0.1f);
}

void Airplane::Draw(Shader& shader, Camera& camera)
{
	model.Draw(shader, camera);
	//model.Draw(shader, camera);
}

void Airplane::Inputs(GLFWwindow* window)
{
	model.Inputs(window);
}
