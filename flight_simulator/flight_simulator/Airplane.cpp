#include "Airplane.h"

Airplane::Airplane() :
	Model("models/second_plane/scene.gltf")
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
	// only one active at a time

	Translation(window);
	//model.Rotation(window);
}

void Airplane::NoViewDraw(Shader& shader, Camera& camera)
{
	SetTransformations(glm::vec3(603.f, -1809.f, -23014.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(5.1f, 5.1f, 5.1f), glm::radians(90.f));
	Model::NoViewDraw(shader, camera);
}

void Airplane::Draw(Shader& shader, Camera& camera)
{
	SetTransformations(glm::vec3(119907.f, 1893.52f, -127622.f), glm::vec3(0.f, -1.f, 0.f), glm::vec3(5.1f, 5.1f, 5.1f), glm::radians(90.f));
	Model::Draw(shader, camera);
}

void Airplane::Draw(Shader& shader, Camera& camera, bool attached)
{
	if (attached)
		Airplane::NoViewDraw(shader, camera);
	else
		Airplane::Draw(shader, camera);
}
