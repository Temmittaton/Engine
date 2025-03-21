#include "Camera.hpp"

// Contructor
Camera::Camera () {
	values = glm::vec4 (1, 1, 0, 0);
	core = Core ();
};

// Methods
glm::mat4 Camera::GetViewMatrix () {
	return glm::mat4 ();
}