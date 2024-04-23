#include "Mesh.h"
#include "Model.h"
#include "SkyBox.h"
#include "Vertices.h"
#include "Init.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#pragma comment (lib, "glfw3dll.lib")
#pragma comment (lib, "glew32.lib")
#pragma comment (lib, "OpenGL32.lib")

void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	Camera* camera = static_cast<Camera*>(glfwGetWindowUserPointer(window));
	if (camera) {
		camera->ProcessMouseScroll(static_cast<float>(yoffset));
	}
}

int main()
{
	GLFWwindow* window = glfwCreateWindow(width, height, "Title", NULL, NULL);
	InitializeWindow(window);

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));
	Model landModel("models/land/scene.gltf");
	Model model("models/plane/scene.gltf");

	Shader shaderProgram("default.vert", "default.frag");
	Shader skyboxShader("skybox.vert", "skybox.frag");
	ActivateShader(shaderProgram);	

	skyboxShader.Activate();
	glUniform1i(glGetUniformLocation(skyboxShader.ID, "skybox"), 0);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CCW);

	BuildSkyBox(skyboxShader);

	glfwSetWindowUserPointer(window, &camera);
	glfwSetScrollCallback(window, ScrollCallback);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.Inputs(window);
		camera.UpdateMatrix(45.0f, 0.1f, 400.0f);
		
		model.Draw(shaderProgram, camera);
		landModel.Draw(shaderProgram, camera);

		glDepthFunc(GL_LEQUAL);
		glDisable(GL_CULL_FACE);

		skyboxShader.Activate();
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);
		// We make the mat4 into a mat3 and then a mat4 again in order to get rid of the last row and column
		// The last row and column affect the translation of the skybox (which we don't want to affect)
		view = glm::mat4(glm::mat3(glm::lookAt(camera.Position, camera.Position + camera.Orientation, camera.Up)));
		projection = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 400.0f);
		glUniformMatrix4fv(glGetUniformLocation(skyboxShader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(skyboxShader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		// Draws the cubemap as the last object so we can save a bit of performance by discarding all fragments
		// where an object is present (a depth of 1.0f will always fail against any object's depth value)
		glBindVertexArray(skyboxVAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glEnable(GL_CULL_FACE);
		glDepthFunc(GL_LESS);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	shaderProgram.Delete();
	skyboxShader.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}