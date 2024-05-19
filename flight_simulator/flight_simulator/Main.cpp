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
bool planeDestroyed = false;
bool gameOverSoundPlayed = false;

std::chrono::time_point<std::chrono::high_resolution_clock> collisionTime;
std::chrono::time_point<std::chrono::high_resolution_clock> crashTime;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
int main()
{
	GLFWwindow* window = glfwCreateWindow(width, height, "Title", NULL, NULL);
	InitializeWindow(window);

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

	Point points1(glm::vec3(-788.f, 41.f, -1047.f), glm::vec3(-520.f, 154.f, -843.f));
	Point points2(glm::vec3(-900.f, 41.f, -864.f), glm::vec3(-620.f, 280.f, -306.f));
	Point points3(glm::vec3(-946.f, 41.f, -308.f), glm::vec3(-604.f, 340.f, 255.f));
	Point points4(glm::vec3(-888.f, 41.f, 290.f), glm::vec3(-667.f, 441.f, 481.f));
	Point points5(glm::vec3(-775.f, 41.f, 513.f), glm::vec3(-559.f, 475.f, 796.f));
	Point points6(glm::vec3(-683.f, 41.f, 805.f), glm::vec3(-505.f, 419.f, 968.f));
	Point points7(glm::vec3(-649.f, 41.f, 993.f), glm::vec3(-524.f, 260.f, 1017.f));
	Point points8(glm::vec3(312.f, 41.f, 133.f), glm::vec3(439.f, 329.f, 283.f));
	Point points9(glm::vec3(184.f, 41.f, -10.f), glm::vec3(224.f, 246.f, 48.f));
	Point points10(glm::vec3(431.f, 41.f, 292.f), glm::vec3(483.f, 280.f, 324.f));
	Point points11(glm::vec3(478.f, 41.f, 323.f), glm::vec3(510.f, 240.f, 351.f));
	Point points12(glm::vec3(477.f, 41.f, 360.f), glm::vec3(540.f, 169.f, 388.f));
	Point points13(glm::vec3(586.f, 41.f, 261.f), glm::vec3(638.f, 114.f, 409.f));
	Point points14(glm::vec3(248.f, 41.f, -14.f), glm::vec3(353.f, 277.f, 125.f));
	Point points15(glm::vec3(216.f, 41.f, -271.f), glm::vec3(524.f, 203.f, -83.f));
	Point points16(glm::vec3(346.f, 41.f, -334.f), glm::vec3(411.f, 299.f, -296.f));
	Point points17(glm::vec3(403.f, 41.f, -671.f), glm::vec3(431.f, 335.f, -361.f));
	Point points18(glm::vec3(407.f, 41.f, -671.f), glm::vec3(538.f, 443.f, -369.f));
	Point points19(glm::vec3(445.f, 41.f, -1009.f), glm::vec3(562.f, 502.f, -697.f));
	Point points20(glm::vec3(429.f, 41.f, -1119.f), glm::vec3(523.f, 395.f, -1008.f));
	Point points21(glm::vec3(473.f, 41.f, -1180.f), glm::vec3(544.f, 354.f, -1109.f));
	Point points22(glm::vec3(467.f, 41.f, -1235.f), glm::vec3(535.f, 318.f, -1174.f));
	Point points23(glm::vec3(447.f, 41.f, -1251.f), glm::vec3(552.f, 310.f, -1183.f));
	Point points24(glm::vec3(314.f, 41.f, -1417.f), glm::vec3(481.f, 232.f, -1221.f));
	Point points25(glm::vec3(537.f, 41.f, -1251.f), glm::vec3(583.f, 232.f, -1157.f));

	Point bpoint01(glm::vec3(1581.26, 10.6445, -1794.53), glm::vec3(1839.84, 68.7172, -1396.4));
	Point bpoint04(glm::vec3(1567.14, 21.0349, -1325.99), glm::vec3(1674.79, 233.561, -1272.87));

	// --------------------------------------------------------------------------------------------


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
	irrklang::ISound* gameOverSound = nullptr;
	irrklang::ISound* restartSound = nullptr;

	glm::mat4 r90 = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, -1.0f, 0.0f));
	glm::mat4 r180 = glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 r120 = glm::rotate(glm::mat4(1.0f), glm::radians(120.0f), glm::vec3(-1.0f, -1.0f, -1.0f));

	//glm::vec3 fireTrans = glm::vec3(1621.21, 1700.91, 420.0);
	glm::vec3 fireTrans = glm::vec3(-8.78998, 2655.91, -625);
	glm::vec3 fireScale = glm::vec3(3.0f, 3.0f, 3.0f);
	fire.SetTransformations(fireTrans, fireScale, r90);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//	airplane.Draw(shadowProgram, camera, attachPlane);

		if (cameraControl)
		{
			if (!camera.hasCollided)
				camera.Inputs(window);
		}
		else
		{
			//model you want to move here
			//! only one model and one movement type
			// ex. model.Rotation() / model.Translation()
			//airplane.Translation(window);
			//road.Rotation(window);
			//FloorRotation(window);
			//hangar.Translation(window);
			fire.Translation(window);
		}

		camera.UpdateMatrix(45.0f, 0.1f, 50000.0f);

		if (camera.hasCollided)
		{
			particles.Draw(particleShader, camera);
			if (!collisionDetected)
			{
				// Play the arcade sound and set its volume
				collisionSound = engine->play2D("sounds/arcade-retro-game-over.wav", false, false, true);
				if (collisionSound)
					collisionSound->setVolume(0.5f);

				collisionDetected = true;
				collisionTime = std::chrono::high_resolution_clock::now();
				gameOverSoundPlayed = false;
			}
			else
			{
				auto currentTime = std::chrono::high_resolution_clock::now();
				auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(currentTime - collisionTime).count();
				if (elapsed >= 3) // delay for five seconds
				{
					fire.NoViewDraw(shaderProgram, camera);
					if (!gameOverSoundPlayed) {
						// Play the crash sound and set its volume
						collisionSound = engine->play2D("sounds/crash.mp3", false, false, true);
						if (collisionSound)
						{
							collisionSound->setVolume(0.2f);
						}
						gameOverSoundPlayed = true;
						crashTime = std::chrono::high_resolution_clock::now();


					}
					planeDestroyed = true;
					//collisionDetected = false;
					//attachPlane = !attachPlane;
					auto currentTime = std::chrono::high_resolution_clock::now();
					auto newelapsed = std::chrono::duration_cast<std::chrono::seconds>(currentTime - crashTime).count();
					if (newelapsed >= 4) // Adjust this value as needed for your desired delay
					{
						attachPlane = !attachPlane;
						collisionDetected = false;
						planeDestroyed = false;
					}
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
		if (attachPlane && !camera.hasCollided && camera.speed > camera.kSlowSpeed)
		{
			airplane.Inputs(window);
		}

		//point.Draw(camera);
		if (!planeDestroyed)
			airplane.Draw(shaderProgram, camera, attachPlane);

		glm::vec3 landScale = glm::vec3(500.0f, 500.0f, 500.0f);
		glm::vec3 landRotation = glm::vec3(1, -232, 0);
		landModel.SetTransformations(glm::vec3(0.0f, -100.0f, 0.0f), landScale);
		landModel.Draw(shaderProgram, camera);

		hangar.SetTransformations(glm::vec3(1625.0f, 1450.0f, 2.0f), glm::vec3(7.5f, 7.5f, 7.5f), r90);
		hangar.Draw(shaderProgram, camera);

		controlTower.SetTransformations(glm::vec3(1620.0f, 110.0f, -1300.0f), glm::vec3(110.0f, 110.0f, 110.0f));
		controlTower.Draw(shaderProgram, camera);

		cat.SetTransformations(glm::vec3(1575.5f, 125.5f, -1300.0f), glm::vec3(3.0f, 3.0f, 3.0f), r180);
		cat.Draw(shaderProgram, camera);

		airstrip.SetTransformations(glm::vec3(372.35f, 430.0f, 27.4f), glm::vec3(12.0f, 12.0f, 12.0f), r120);
		airstrip.Draw(shaderProgram, camera);

		tent.SetTransformations(glm::vec3(1485.0f, 1850.0f, 2.0f), glm::vec3(4.0f, 4.0f, 4.0f), r90);
		tent.Draw(shaderProgram, camera);
		points1.Draw(camera);
		points2.Draw(camera);
		points3.Draw(camera);
		points4.Draw(camera);
		points5.Draw(camera);
		points6.Draw(camera);
		points7.Draw(camera);
		points8.Draw(camera);
		points9.Draw(camera);
		points10.Draw(camera);
		points11.Draw(camera);
		points12.Draw(camera);
		points13.Draw(camera);
		points14.Draw(camera);
		points15.Draw(camera);
		points16.Draw(camera);
		points17.Draw(camera);
		points18.Draw(camera);
		points19.Draw(camera);
		points20.Draw(camera);
		points21.Draw(camera);
		points22.Draw(camera);
		points23.Draw(camera);
		points24.Draw(camera);
		points25.Draw(camera);

		bpoint01.Draw(camera);
		bpoint04.Draw(camera);

		float distanceFromCamera = 50.f;
		//fire.SetTransformations(fireTrans + camera.Position * 10.f + distanceFromCamera * camera.Orientation, fireScale, r90);
		//fire.Draw(shaderProgram, camera);
		//fire.NoViewDraw(shaderProgram, camera);

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
		collisionDetected = false;
		planeDestroyed = false;
	}
}