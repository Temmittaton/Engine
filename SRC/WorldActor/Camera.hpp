#ifndef _CAMERA_

#define _CAMERA_

#include "Core.hpp"
#include <glm.hpp>

class Camera {
public :
	// Attributes
	glm::vec4 values; // Size in x, size in y, idk, idk
	glm::vec4 rotation;
	Core core;

	// Constructors
	Camera ();

	// Methods
	glm::mat4 GetViewMatrix ();

	glm::vec4 forward () const;
	glm::vec4 up () const;
	glm::vec4 right () const;
};

#endif _CAMERA_