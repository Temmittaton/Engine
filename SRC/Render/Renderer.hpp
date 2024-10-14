#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "../World/World.h"
#include "../World/Scene.h"

class Renderer {
public:
	GLFWwindow* window;
	float quad [20];
	unsigned int shader, VBO, VAO;

	// Constructors
	Renderer () {};

	void RenderInit ();
	void RenderFrame (World &world);
};

