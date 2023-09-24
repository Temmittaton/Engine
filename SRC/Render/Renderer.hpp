#pragma once

class Renderer {
private :
	GLFWwindow* window;

public :
	// Constructors
	Renderer ();

	void RenderFrame ();
};

