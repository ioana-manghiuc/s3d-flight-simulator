#include "Mesh.h"
#include "Model.h"
#include "SkyBox.h"
#include "Vertices.h"
#include "Init.h"
#include "Airplane.h"
#include "Point.h"
#include "irrKlang.h"
#include <chrono>
#include <thread>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#pragma comment (lib, "glfw3dll.lib")
#pragma comment (lib, "glew32.lib")
#pragma comment (lib, "OpenGL32.lib")
#pragma comment(lib, "irrKlang.lib")

float scale = 1.0f;
float shaderLocation;
float skyboxLocation;

Shader shaderProgram;
Shader skyboxShader;
Shader shadowProgram;

bool cameraControl = true;
bool attachPlane = false;
bool collisionDetected = false;
std::chrono::time_point<std::chrono::high_resolution_clock> collisionTime;

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

	Particles particles;
	Shader particleShader("particles.vert", "particles.frag");
	
	Camera camera(width, height);
	camera.Orientation = glm::vec3(0.871424, 1.7049e-07, 0.49052);

	Airplane airplane;
	Model landModel("models/terrain/scene.gltf");
	Model airstrip("models/airstrip/scene.gltf");
	Model hangar("models/hangar/scene.gltf");
	Model controlTower("models/control_tower/scene.gltf");
	Model fire("models/fire/scene.gltf");
	Model cat("models/cat/scene.gltf");	
	Model tent("models/tent/scene.gltf");

	shaderProgram = Shader("default.vert", "default.frag");
	skyboxShader = Shader("skybox.vert", "skybox.frag");
	shadowProgram = Shader("shadowMap.vert", "shadowMap.frag");
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


	glm::mat4 orthgonalProjection = glm::ortho(-35.0f, 35.0f, -35.0f, 35.0f, 0.1f, 75.0f);
	glm::mat4 lightView = glm::lookAt(20.0f * lightPos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 lightProjection = orthgonalProjection * lightView;

	//shadowProgram.Activate();
	//glUniformMatrix4fv(glGetUniformLocation(shadowProgram.ID, "lightProjection"), 1, GL_FALSE, glm::value_ptr(lightProjection));

	//unsigned int FBO;
	//glGenFramebuffers(1, &FBO);
	//glBindFramebuffer(GL_FRAMEBUFFER, FBO);


	//Point point(camera.kBasePosition, camera.kBasePosition + 10.f);

	irrklang::ISoundEngine* engine = irrklang::createIrrKlangDevice();

	if (!engine)
		std::cout << "Error starting up engine!\n" << std::endl;

	irrklang::ISound* collisionSound = nullptr;

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//	airplane.Draw(shadowProgram, camera, attachPlane);

		if (cameraControl)
		{
			if(!camera.hasCollided)
				camera.Inputs(window);
		}
		else
		{
			//model you want to move here
			//! only one model and one movement type
			// ex. model.Rotation() / model.Translation()
			airplane.Translation(window);
			//road.Rotation(window);
			//FloorRotation(window);
			//hangar.Translation(window);
			//fire.Translation(window);
		}
		
		camera.UpdateMatrix(45.0f, 0.1f, 50000.0f);

		if (camera.hasCollided)
		{
			particles.Draw(particleShader, camera);
			if (!collisionDetected)
			{
				collisionSound = engine->play2D("sounds/arcade-retro-game-over.wav", false, false, true);
				collisionDetected = true;
				collisionTime = std::chrono::high_resolution_clock::now();
			}
			else
			{
				auto currentTime = std::chrono::high_resolution_clock::now();
				auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(currentTime - collisionTime).count();
				if (elapsed >= 5) // delay for five seconds
				{
					attachPlane = !attachPlane;
					collisionDetected = false;
				}
			}
		}
		else if (collisionSound != nullptr)
		{
			collisionSound->stop();
			collisionSound->drop();
			collisionSound = nullptr;
		}
		
		camera.SetIsAttached(attachPlane);
		if (attachPlane && !camera.hasCollided)
		{
			airplane.Inputs(window);
		}
		
		//point.Draw(camera);
		
		airplane.Draw(shaderProgram, camera, attachPlane);

		glm::vec3 landScale = glm::vec3(500.0f, 500.0f, 500.0f);
		glm::vec3 landRotation = glm::vec3(1, -232, 0);
		landModel.SetTransformations(glm::vec3(0.0f, -100.0f, 0.0f), landScale);
		landModel.Draw(shaderProgram, camera);

		glm::mat4 r90 = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, -1.0f, 0.0f));
		glm::mat4 r180 = glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 r120 = glm::rotate(glm::mat4(1.0f), glm::radians(120.0f), glm::vec3(-1.0f, -1.0f, -1.0f));

		hangar.SetTransformations(glm::vec3(1625.0f, 1450.0f, 2.0f), glm::vec3(7.5f, 7.5f, 7.5f), r90);
		hangar.Draw(shaderProgram, camera);

		controlTower.SetTransformations(glm::vec3(1620.0f, 110.0f, -1300.0f), glm::vec3(110.0f, 110.0f, 110.0f));
		controlTower.Draw(shaderProgram, camera);

		cat.SetTransformations(glm::vec3(1575.5f, 125.5f, -1300.0f), glm::vec3(3.0f, 3.0f, 3.0f), r180);
		cat.Draw(shaderProgram, camera);
		
		airstrip.SetTransformations(glm::vec3(372.35f, 430.0f, 24.4f), glm::vec3(12.0f, 12.0f, 12.0f), r120);
		airstrip.Draw(shaderProgram, camera);

		tent.SetTransformations(glm::vec3(1485.0f, 1850.0f, 2.0f), glm::vec3(4.0f, 4.0f, 4.0f), r90);
		tent.Draw(shaderProgram, camera);

		//fire.SetTransformations(glm::vec3(1621.21, 1700.91, 420.0), glm::vec3(10.0f, 10.0f,10.0f), r90);
		//fire.Draw(shaderProgram, camera);

		glDepthFunc(GL_LEQUAL);
		glDisable(GL_CULL_FACE);

		skyboxShader.Activate();
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);
		view = glm::mat4(glm::mat3(glm::lookAt(camera.Position, camera.Position + camera.Orientation, camera.Up)));
		projection = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 1000.0f);
		glUniformMatrix4fv(glGetUniformLocation(skyboxShader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(skyboxShader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

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
	shadowProgram.Delete();
	engine->drop();

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