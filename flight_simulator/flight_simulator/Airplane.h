#ifndef AIRPLANE_CLASS_H
#define AIRPLANE_CLASS_H
#include "Model.h"

class Airplane : public Model
{
public:
	Airplane();
	//void Draw(Shader& shader, Camera& camera, glm::vec3 translation, glm::vec3 rotation, glm::vec3 scale);
	void Inputs(GLFWwindow* window);
	void NoViewDraw(Shader& shader, Camera& camera);
	void Draw(Shader& shader, Camera& camera);
	void Draw(Shader& shader, Camera& camera, bool attached);

public:
	const glm::vec3 kBaseRotation;
	const glm::vec3 kUpRotation;
	const glm::vec3 kDownRotation;
	const glm::vec3 kLeftRotation;
	const glm::vec3 kRightRotation;
};
#endif
