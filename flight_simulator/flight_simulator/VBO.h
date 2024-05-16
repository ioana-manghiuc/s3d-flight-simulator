#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<vector>

#include <GL/glew.h>
#include <GLM.hpp>

struct Vertex
{
	glm::vec3 positions;
	glm::vec3 normal;
	glm::vec3 color;
	glm::vec2 texUV;
};

class VBO
{
public:
	GLuint ID;

	VBO(std::vector<Vertex>& vertices);
	VBO(GLfloat* vertices, GLsizeiptr size);

	void Bind();
	void Unbind();
	void Delete();
};

#endif


