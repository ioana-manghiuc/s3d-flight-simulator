#ifndef AIRPLANE_CLASS_H
#define AIRPLANE_CLASS_H
#include "Model.h"

class Airplane
{
public:
	Airplane();
	Airplane(glm::vec3 pos);
	void Draw(Shader& shader, Camera& camera);
	void Draw(Shader& shader, Camera& camera, glm::vec3 translation, glm::vec3 rotation, glm::vec3 scale);
	void Inputs(GLFWwindow* window);

public:
	Model model;
};
#endif
