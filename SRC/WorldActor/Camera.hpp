#ifndef _CAMERA_

#define _CAMERA_

#include "Core.hpp"
#include <glm/vec4.hpp>

class Camera {
public :
	// Attributes
	glm::vec4 values; // Size in x, size in y, idk, idk
	Core core;

	// Constructors
	Camera ();

	// Methods
	glm::mat4 GetViewMatrix ();
};

#endif _CAMERA_