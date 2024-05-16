#ifndef POINT_H
#define POINT_H

#include "Particles.h"


class Point
{
public:
	Point(const glm::vec3& lower, const glm::vec3& upper);

	void Draw(Camera& camera);
private:
	Shader m_shader;
	VAO VAO1;
	std::vector<glm::vec3> m_positions;
};

#endif