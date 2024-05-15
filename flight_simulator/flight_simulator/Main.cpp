#include "Mesh.h"
#include "Model.h"
#include "SkyBox.h"
#include "Vertices.h"
#include "Init.h"
#include "Airplane.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#pragma comment (lib, "glfw3dll.lib")
#pragma comment (lib, "glew32.lib")
#pragma comment (lib, "OpenGL32.lib")
float scale = 1.0f;
float shaderLocation;
float skyboxLocation;

Shader shaderProgram;
Shader skyboxShader;

bool cameraControl = true;
bool attachPlane = false;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
int main()
{
	GLFWwindow* window = glfwCreateWindow(width, height, "Title", NULL, NULL);
	InitializeWindow(window);

	auto campos = glm::vec3(205.0f, 83.0f, -444.0f);
	auto planepos = glm::vec3(-96.0f, 400.0f, 50.0f);
	auto dist = campos - planepos;
	std::cout << "offset: " << dist.x << "," << dist.y << "," << dist.z << std::endl;
	Texture textures[]
	{
		Texture("planks.png", "diffuse",0),
		Texture("planksSpec.png", "specular",1),
	};


	//Airplane airplane(planepos);
	//Model airplane("models/plane/scene.gltf");
	Model propeller("models/airplane_propeller/scene.gltf");
	
	glm::vec3 cameraPosition = glm::vec3(1557.73, 45.2891, -944.709);
	// old camera position
	//glm::vec3 cameraPosition = glm::vec3(204.159, 83.0502, -443.938);
	Camera camera(width, height, cameraPosition);
	//airplane.SetTransformations(glm::vec3(-96.0f, 400.0f, 50.0f), glm::vec3(163.0f, -1171.0f, 175.0f), glm::vec3(0.1f, 0.1f, 0.1f));
	//airplane.translation = planepos;
	camera.Orientation = glm::vec3(-0.405053, -0.0952021, 0.909321);
	Airplane airplane;
	Model landModel("models/terrain/scene.gltf");
	Model road("models/road/scene.gltf");

	shaderProgram = Shader("default.vert", "default.frag");
	skyboxShader = Shader("skybox.vert", "skybox.frag");
	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);
	shaderLocation = glGetUniformLocation(shaderProgram.ID, "colorScale");
	skyboxLocation = glGetUniformLocation(skyboxShader.ID, "colorScale");

	shaderProgram.Activate();
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	glUniform1f(shaderLocation, scale);

	skyboxShader.Activate();
	glUniform1i(glGetUniformLocation(skyboxShader.ID, "skybox"), 0);
	glUniform1f(skyboxLocation, scale);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CCW);

	BuildSkyBox(skyboxShader);

	glfwSetWindowUserPointer(window, &camera);
	glfwSetScrollCallback(window, ScrollCallback);
	glfwSetKeyCallback(window, key_callback);   

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (cameraControl)
			camera.Inputs(window);
		else
		{
			//model you want to move here
			//! only one model and one movement type
			// ex. model.Rotation() / model.Translation()
			//airplane.Inputs(window);
			//road.Rotation(window);
			//FloorRotation(window);
		}

		camera.UpdateMatrix(45.0f, 0.1f, 50000.0f);

		// normal plane
		//airplane.Draw(shaderProgram, camera);
		
		//attached plane
		//airplane.NoViewDraw(shaderProgram, camera);
		
		//floor.Draw(shaderProgram, camera, floorTranslation, floorRotation, floorScale);

		//std::cout << "CAMERA POS: (" << camera.Position.x << ", " << camera.Position.y << ", " << camera.Position.z << ")\n";
		//std::cout << "CAMERA ORIENTATION: (" << camera.Orientation.x << ", " << camera.Orientation.y << ", " << camera.Orientation.z << ")\n";
		//airplane.translation = camera.PlanePosition - dist;
		//airplane.rotation = camera.PlaneRotation;
		//airplane.Draw(shaderProgram, camera);		
		//airplane.Draw(shaderProgram, camera);
		
		if (attachPlane)
		{
			airplane.Inputs(window);
		}

		airplane.Draw(shaderProgram, camera, attachPlane);
		camera.SetIsAttached(attachPlane);

		glm::vec3 landScale = glm::vec3(500.0f, 500.0f, 500.0f);
		glm::vec3 landRotation = glm::vec3(1, -232, 0);
		//road.Draw(shaderProgram, camera,glm::vec3( 1.0f,1.0f,1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(10.0f, 10.0f, 10.0f));
		//propeller.Draw(shaderProgram, camera,glm::vec3( 1.0f,1.0f,1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(10.0f, 10.0f, 10.0f));
		landModel.SetTransformations(glm::vec3(0.0f, -100.0f, 0.0f), landScale);
		landModel.Draw(shaderProgram, camera);

		glDepthFunc(GL_LEQUAL);
		glDisable(GL_CULL_FACE);

		skyboxShader.Activate();
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);
		// We make the mat4 into a mat3 and then a mat4 again in order to get rid of the last row and column
		// The last row and column affect the translation of the skybox (which we don't want to affect)
		view = glm::mat4(glm::mat3(glm::lookAt(camera.Position, camera.Position + camera.Orientation, camera.Up)));
		projection = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 1000.0f);
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

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
	{
		if (scale >= 0.2)
		{
			scale -= 0.1f;
			if (scale < 0.2) {
				LoadCubemap(nightSkybox);
			}
			shaderProgram.Activate();
			glUniform1f(shaderLocation, scale);
			skyboxShader.Activate();
			glUniform1f(skyboxLocation, scale);
		}
	}
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
	{
		if (scale < 1)
		{
			if (scale >= 0.2) {
				LoadCubemap(daySkybox);
			}
			scale += 0.1f;
			shaderProgram.Activate();
			glUniform1f(shaderLocation, scale);
			skyboxShader.Activate();
			glUniform1f(skyboxLocation, scale);
		}
	}
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
	{
		cameraControl = !cameraControl;
	}
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
	{
		attachPlane = !attachPlane;
	}
}