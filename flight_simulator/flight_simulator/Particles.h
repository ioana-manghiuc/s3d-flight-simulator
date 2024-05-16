#ifndef PARTICLES_H
#define PARTICLES_H
#include <vector>

#include <GL/glew.h>
#include <glfw3.h>

#include <GLM.hpp>

#include "Texture.h"
#include "Camera.h"

#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include <GLM.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

class Particles
{
public:
	Particles();

	void Draw(Shader& shader, Camera& camera);
private:
	VAO VAO1;

	// Vertices coordinates
};

#endif