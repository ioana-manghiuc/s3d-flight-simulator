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
	const glm::vec3 kNoViewTranslation = glm::vec3(48.f, -1809.f, -23014.5f);
	const glm::vec3 kScale = glm::vec3(2.7f, 2.7f, 2.7f);
	const glm::vec3 kNoViewScale = glm::vec3(4.7f, 4.7f, 4.7f);

	const glm::mat4 kBaseRotation = glm::rotate(glm::mat4(1.0f), glm::radians(90.f), glm::vec3(0.0f, 1.0f, 0.0f));
	const glm::mat4 kUpRotation = glm::rotate(glm::mat4(1.0f), glm::radians(30.f), glm::vec3(0.0f, 0.0f, 1.0f));
	const glm::mat4 kDownRotation = glm::rotate(glm::mat4(1.0f), glm::radians(30.f), glm::vec3(0.0f, 0.0f, -1.0f));
	const glm::mat4 kRightRotation = glm::rotate(glm::mat4(1.0f), glm::radians(30.f), glm::vec3(1.0f, 0.0f, 0.0f));
	const glm::mat4 kLeftRotation = glm::rotate(glm::mat4(1.0f), glm::radians(30.f), glm::vec3(-1.0f, 0.0f, 0.0f));

	const glm::vec3 kUpAxis = glm::vec3(0.0f, 0.0f, 1.0f);
	const glm::vec3 kDownAxis = glm::vec3(0.0f, 0.0f, -1.0f);
	const glm::vec3 kRightAxis = glm::vec3(1.0f, 0.0f, 0.0f);
	const glm::vec3 kLeftAxis = glm::vec3(-1.0f, 0.0f, 0.0f);

	const float kMaxUpDownAngle = 20.f;
	const float kMaxLeftRightAngle = 30.f;

	float m_upAngle = 0.0f;
	float m_downAngle = 0.0f;
	float m_rightAngle = 0.0f;
	float m_leftAngle = 0.0f;
};
#endif
