#ifndef _CAMERA_

#define _CAMERA_

#include "WorldActor.hpp"

class WorldActor;

class Camera : public WorldActor {
public :
	// Attributes
	int fov = 90;

	// Constructors
	Camera ();

	// Methods
	glm::mat4 GetViewMatrix ();
};

#endif _CAMERA_