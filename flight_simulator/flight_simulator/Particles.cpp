#include "Particles.h"
#include<random>

float vertices[] = {
    // Front face
    -0.5f,  0.5f, 0.5f,   1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, 0.5f,   1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, 0.5f,   1.0f, 0.0f, 0.0f,
     0.5f,  0.5f, 0.5f,   1.0f, 0.0f, 0.0f,

     // Back face
     -0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,
     -0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,
     0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,

     // Right face
     0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,
     0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,

     // Left face
     -0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 0.0f,
     -0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 0.0f,
     -0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,
     -0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,

     // Top face
     -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
     -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
     0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 0.0f,

     // Bottom face
     -0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 0.0f,
     -0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 0.0f
};

std::vector<GLuint> indices = {
    0, 1, 2,
    2, 3, 0,
    4, 5, 6,
    6, 7, 4,
    8, 9, 10,
    10, 11, 8,
    12, 13, 14,
    14, 15, 12,
    16, 17, 18,
    18, 19, 16,
    20, 21, 22,
    22, 23, 20
};

//GLfloat vertices[] =
//{ //     COORDINATES     /        COLORS 
//	-0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f, //0
//	-0.5f,  0.5f, 0.0f,     1.0f, 0.0f, 0.0f, //1
//	 0.5f,  0.5f, 0.0f,     1.0f, 0.0f, 0.0f, //2
//	 0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f //3
//};
//
//
//
//// Indices for vertices order
//std::vector<GLuint> indices =
//{
//	0, 2, 1, // Upper triangle
//	0, 3, 2 // Lower triangle
//};

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
    glDisable(GL_CULL_FACE);

	shader.Activate();

	glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
	camera.Matrix(shader, "camMatrix");

	int max = 5;
    float scaleFactor = 0.5f;
    float distanceFromCamera = 50.f;

    float xRange = 10.0f;
    float zRange = 10.0f;
    float yRange = 4.0f;

	for (int i = 1; i < max; i++)
	{
		VAO1.Bind();
		glm::mat4 model = glm::mat4(1.0f);
		//glm::vec3 translation = glm::vec3(GetRandomNum(-i / 5, i / 5), GetRandomNum(-i , i), GetRandomNum(-i / 5, i / 5));
		glm::vec3 translation = glm::vec3(GetRandomNum(-xRange, xRange), GetRandomNum(-yRange, yRange), GetRandomNum(-zRange, zRange));
        model = glm::translate(model, glm::vec3(0.0, -3.0, 0.0));
		model = glm::translate(model, translation);
		model = glm::translate(model, camera.Position + distanceFromCamera * camera.Orientation);
		
		model = glm::scale(model, glm::vec3(scaleFactor));
		glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CCW);
}
