#include "../World/World.h"

#pragma once

class Renderer {
public:
	GLFWwindow* window;
	float quad [20];
	unsigned int shader, VBO, VAO;

	// Constructors
	Renderer () {};

	void RenderInit ();
	void RenderFrame (World* world);
};

