#include "WorldActor.hpp"

#pragma once
class Camera : public WorldActor {
public :
	// Attributes
	int fov = 90;

	// Constructors
	Camera ();

	// Methods
	glm::mat4 GetViewMatrix ();
};
