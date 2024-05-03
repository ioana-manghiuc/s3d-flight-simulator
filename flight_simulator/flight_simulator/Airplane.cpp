#include "Airplane.h"

Airplane::Airplane():
	model{ "models/plane/scene.gltf" }
{
	translation = glm::vec3(-125.0f, 500.0f, 0.0f);
	rotation = glm::quat(1.0f, 0.0f, -0.45f, 0.0f);
	scale = glm::vec3(0.1f, 0.1f, 0.1f);
}

void Airplane::Draw(Shader& shader, Camera& camera)
{
	model.Draw(shader, camera, translation, rotation, scale);
}
