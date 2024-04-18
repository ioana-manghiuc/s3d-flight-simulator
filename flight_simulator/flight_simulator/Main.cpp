#include "Mesh.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#pragma comment (lib, "glfw3dll.lib")
#pragma comment (lib, "glew32.lib")
#pragma comment (lib, "OpenGL32.lib")

const unsigned width = 800;
const unsigned height = 800;

Vertex vertices[] =
{ //               COORDINATES           /            COLORS          /           NORMALS         /       TEXTURE COORDINATES    //
	Vertex{glm::vec3(-1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3(1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3(1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)}
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3
};

Vertex lightVertices[] =
{ //     COORDINATES     //
	Vertex{glm::vec3(-0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f,  0.1f,  0.1f)}
};

GLuint lightIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};

std::vector<Vertex> skyboxVertices2 = {
	// Positions
	Vertex(glm::vec3(-1.0f,  1.0f, -1.0f), glm::vec3(0.0f), glm::vec3(0.0f), glm::vec2(0.0f)),
	Vertex(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.0f), glm::vec3(0.0f), glm::vec2(0.0f)),
	Vertex(glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(0.0f), glm::vec3(0.0f), glm::vec2(0.0f)),
	Vertex(glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(0.0f), glm::vec3(0.0f), glm::vec2(0.0f)),
	Vertex(glm::vec3(1.0f,  1.0f, -1.0f), glm::vec3(0.0f), glm::vec3(0.0f), glm::vec2(0.0f)),
	Vertex(glm::vec3(-1.0f,  1.0f, -1.0f), glm::vec3(0.0f), glm::vec3(0.0f), glm::vec2(0.0f)),

	Vertex(glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec3(0.0f), glm::vec3(0.0f), glm::vec2(0.0f)),
	Vertex(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.0f), glm::vec3(0.0f), glm::vec2(0.0f)),
	Vertex(glm::vec3(-1.0f,  1.0f, -1.0f), glm::vec3(0.0f), glm::vec3(0.0f), glm::vec2(0.0f)),
	Vertex(glm::vec3(-1.0f,  1.0f, -1.0f), glm::vec3(0.0f), glm::vec3(0.0f), glm::vec2(0.0f)),
	Vertex(glm::vec3(-1.0f,  1.0f,  1.0f), glm::vec3(0.0f), glm::vec3(0.0f), glm::vec2(0.0f)),
	Vertex(glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec3(0.0f), glm::vec3(0.0f), glm::vec2(0.0f)),

	Vertex(glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(0.0f), glm::vec3(0.0f), glm::vec2(0.0f)),
	Vertex(glm::vec3(1.0f, -1.0f,  1.0f), glm::vec3(0.0f), glm::vec3(0.0f), glm::vec2(0.0f)),
	Vertex(glm::vec3(1.0f,  1.0f,  1.0f), glm::vec3(0.0f), glm::vec3(0.0f), glm::vec2(0.0f)),
	Vertex(glm::vec3(1.0f,  1.0f,  1.0f), glm::vec3(0.0f), glm::vec3(0.0f), glm::vec2(0.0f)),
	Vertex(glm::vec3(1.0f,  1.0f, -1.0f), glm::vec3(0.0f), glm::vec3(0.0f), glm::vec2(0.0f)),
	Vertex(glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(0.0f), glm::vec3(0.0f), glm::vec2(0.0f)),

	Vertex(glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec3(0.0f), glm::vec3(0.0f), glm::vec2(0.0f)),
	Vertex(glm::vec3(-1.0f,  1.0f,  1.0f), glm::vec3(0.0f), glm::vec3(0.0f), glm::vec2(0.0f)),
	Vertex(glm::vec3(1.0f,  1.0f,  1.0f), glm::vec3(0.0f), glm::vec3(0.0f), glm::vec2(0.0f)),
	Vertex(glm::vec3(1.0f,  1.0f,  1.0f), glm::vec3(0.0f), glm::vec3(0.0f), glm::vec2(0.0f)),
	Vertex(glm::vec3(1.0f, -1.0f,  1.0f), glm::vec3(0.0f), glm::vec3(0.0f), glm::vec2(0.0f)),
	Vertex(glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec3(0.0f), glm::vec3(0.0f), glm::vec2(0.0f)),

	Vertex(glm::vec3(-1.0f,  1.0f, -1.0f), glm::vec3(0.0f), glm::vec3(0.0f), glm::vec2(0.0f)),
	Vertex(glm::vec3(1.0f,  1.0f, -1.0f), glm::vec3(0.0f), glm::vec3(0.0f), glm::vec2(0.0f)),
	Vertex(glm::vec3(1.0f,  1.0f,  1.0f), glm::vec3(0.0f), glm::vec3(0.0f), glm::vec2(0.0f)),
	Vertex(glm::vec3(1.0f,  1.0f,  1.0f), glm::vec3(0.0f), glm::vec3(0.0f), glm::vec2(0.0f)),
	Vertex(glm::vec3(-1.0f,  1.0f,  1.0f), glm::vec3(0.0f), glm::vec3(0.0f), glm::vec2(0.0f)),
	Vertex(glm::vec3(-1.0f,  1.0f, -1.0f), glm::vec3(0.0f), glm::vec3(0.0f), glm::vec2(0.0f)),

	Vertex(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.0f), glm::vec3(0.0f), glm::vec2(0.0f)),
	Vertex(glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec3(0.0f), glm::vec3(0.0f), glm::vec2(0.0f)),
	Vertex(glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(0.0f), glm::vec3(0.0f), glm::vec2(0.0f)),
	Vertex(glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(0.0f), glm::vec3(0.0f), glm::vec2(0.0f)),
	Vertex(glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec3(0.0f), glm::vec3(0.0f), glm::vec2(0.0f)),
	Vertex(glm::vec3(1.0f, -1.0f,  1.0f), glm::vec3(0.0f), glm::vec3(0.0f), glm::vec2(0.0f))
};

std::vector<float> skyboxVertices
{
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f
};

std::vector<GLuint> skyboxIndices = {
		1, 2, 6,
	6, 5, 1,
	// Left
	0, 4, 7,
	7, 3, 0,
	// Top
	4, 5, 6,
	6, 7, 4,
	// Bottom
	0, 3, 2,
	2, 1, 0,
	// Back
	0, 1, 5,
	5, 4, 0,
	// Front
	3, 7, 6,
	6, 2, 3
};

std::string faces[6] = {
			"../Skybox/right.jpg",
			"../Skybox/left.jpg",
			"../Skybox/up.jpg",
			"../Skybox/down.jpg",
			"../Skybox/front.jpg",
			"../Skybox/back.jpg"
};

unsigned int loadCubemap(std::vector<std::string> faces)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
			);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, "flight simulator!", NULL, NULL);

	//error check
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glViewport(0, 0, width, height); //specify view port
	glewInit();	

	Texture textures[]
	{
		Texture("planks.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
		Texture("planksSpec.png", "specular", 1, GL_RED, GL_UNSIGNED_BYTE)
	};

	Shader shaderProgram("default.vert", "default.frag");
	shaderProgram.Activate();
	std::vector <Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
	std::vector <GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));
	std::vector <Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));

	Mesh floor(verts, ind, tex);


	Shader lightShader("light.vert", "light.frag");

	std::vector <Vertex> lightVerts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
	std::vector <GLuint> lightInd(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint));

	Mesh light(lightVerts, lightInd, tex);

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 floorPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 floorModel = glm::mat4(1.0f);
	floorModel = glm::translate(floorModel, floorPos);

	Shader skyboxShader("skybox.vert", "skybox.frag");

	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(floorModel));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

	skyboxShader.Activate();
	glUniform1i(glGetUniformLocation(skyboxShader.ID, "skybox"), 0);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE); // cull facing
	glCullFace(GL_FRONT); 	// keeps front faces
	glFrontFace(GL_CCW); 	// uses counter clock-wise standard

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	// create a skybox VAO, VBO, and EBO
	unsigned int skyboxVAO, skyboxVBO, skyboxEBO;
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glGenBuffers(1, &skyboxEBO);

	// bind skybox VAO
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, skyboxVertices.size() * sizeof(float), &skyboxVertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyboxEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, skyboxIndices.size() * sizeof(unsigned int), &skyboxIndices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	unsigned int cubemapTexture;
	glGenTextures(1, &cubemapTexture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	for (unsigned int i = 0; i < 6; i++)
	{
		int width, height, nrChannels;
		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			stbi_set_flip_vertically_on_load(false);
			glTexImage2D
			(
				GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0,
				GL_RGB,
				width,
				height,
				0,
				GL_RGB,
				GL_UNSIGNED_BYTE,
				data
			);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Failed to load texture: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}

	// Main rendering loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.Inputs(window);
		camera.updateMatrix(45.0f, 0.1f, 100.0f);

		floor.Draw(shaderProgram, camera);
		light.Draw(lightShader, camera);

		glDepthFunc(GL_LEQUAL);

		skyboxShader.Activate();
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);
		view = glm::mat4(glm::mat3(glm::lookAt(camera.Position, camera.Position + camera.Orientation, camera.Up)));
		projection = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);
		glUniformMatrix4fv(glGetUniformLocation(skyboxShader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(skyboxShader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glBindVertexArray(skyboxVAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glDepthFunc(GL_LESS); 	// switch back to normal depth function

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	lightShader.Delete();
	shaderProgram.Delete();
	skyboxShader.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}