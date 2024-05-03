#ifndef AIRPLANE_CLASS_H
#define AIRPLANE_CLASS_H
#include "Model.h"

class Airplane
{
public:
	Airplane();

	void Draw(Shader& shader, Camera& camera);
	
	void Inputs(GLFWwindow* window);
private:
	Model model;
};
#endif
