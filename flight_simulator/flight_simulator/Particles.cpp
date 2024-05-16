#include "Particles.h"
#include<random>

GLfloat vertices[] =
{ //     COORDINATES     /        COLORS 
	-0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f, //0
	-0.5f,  0.5f, 0.0f,     1.0f, 0.0f, 0.0f, //1
	 0.5f,  0.5f, 0.0f,     1.0f, 0.0f, 0.0f, //2
	 0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f //3
};



// Indices for vertices order
std::vector<GLuint> indices =
{
	0, 2, 1, // Upper triangle
	0, 3, 2 // Lower triangle
};

float GetRandomNum(int min_value, int max_value)
{
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_real_distribution<float> distribution(min_value, max_value);

	return distribution(gen);
}

Particles::Particles()
{
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices);

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();
}

void Particles::Draw(Shader& shader, Camera& camera)
{
	shader.Activate();

	glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
	camera.Matrix(shader, "camMatrix");

	int max = 500;
	for (int i = 1; i < 100; i++)
	{
		VAO1.Bind();
		glm::mat4 model = glm::mat4(1.0f);
		//model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
		glm::vec3 translation = glm::vec3(GetRandomNum(-i / 5, i / 5), GetRandomNum(-i / 5, i), GetRandomNum(-i / 5, i / 5));
		model = glm::translate(model, translation);
		model = glm::translate(model, camera.Position);
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));

		//shader.SetMat4("model", model);
		glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
}
