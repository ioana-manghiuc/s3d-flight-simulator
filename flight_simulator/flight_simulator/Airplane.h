#ifndef AIRPLANE_CLASS_H
#define AIRPLANE_CLASS_H
#include "Model.h"

class Airplane
{
public:
	glm::vec3 translation;
	glm::quat rotation;
	glm::vec3 scale;

	Airplane();

	void Draw(Shader& shader, Camera& camera);
private:
	Model model;
};
#endif
