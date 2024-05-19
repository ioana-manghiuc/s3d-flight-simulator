#include "Point.h"

float verts[] = {
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

std::vector<GLuint> inds = {
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

Point::Point(const glm::vec3& lower, const glm::vec3& upper):
	m_shader("particles.vert", "particles.frag")
{
    if (lower.x > upper.x or lower.y > upper.y or lower.z > lower.z)
        std::cout << "invalid point";
	VAO1.Bind();

	VBO VBO1(verts, sizeof(verts));
	EBO EBO1(inds);

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

    m_positions.push_back(lower);
    m_positions.push_back(glm::vec3(lower.x, lower.y, upper.z));
    m_positions.push_back(glm::vec3(lower.x, upper.y, lower.z));
    m_positions.push_back(glm::vec3(upper.x, lower.y, lower.z));
    m_positions.push_back(glm::vec3(lower.x, upper.y, upper.z));
    m_positions.push_back(glm::vec3(upper.x, lower.y, upper.z));
    m_positions.push_back(glm::vec3(upper.x, upper.y, lower.z));
    m_positions.push_back(upper);
}

void Point::Draw(Camera& camera)
{
    glDisable(GL_CULL_FACE);

    m_shader.Activate();
    glUniform3f(glGetUniformLocation(m_shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
    camera.Matrix(m_shader, "camMatrix");

    float scaleFactor = 5.0;

    for (const auto& trans : m_positions)
    {
        VAO1.Bind();
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, trans);
        model = glm::scale(model, glm::vec3(scaleFactor));

        glUniformMatrix4fv(glGetUniformLocation(m_shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    }

    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CCW);
}
