#include "Camera.hpp"

// Contructor
Camera::Camera () {
	core = Core ();
};

// Methods
glm::mat4 Camera::GetViewMatrix () {
	return glm::mat4 ();
}