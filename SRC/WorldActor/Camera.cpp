#include "Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

// Contructor
Camera::Camera () {
	values = glm::vec4 (1, 1, 0, 0);
	rotation = glm::vec4 (0);
	core = Core ();
};

// Methods
glm::mat4 Camera::GetViewMatrix () {
	return glm::mat4 ();
}

glm::vec4 Camera::forward () const {
	glm::mat4 m = glm::rotate (glm::mat4 (1.0f), rotation.x, glm::vec3 (1, 0, 0));
	m = glm::rotate (m, rotation.y, glm::vec3 (0, 1, 0));
	m = glm::rotate (m, rotation.z, glm::vec3 (0, 0, 1));
	return m * glm::vec4 (0, 0, 1, 0);
}
glm::vec4 Camera::up () const {
	glm::mat4 m = glm::rotate (glm::mat4 (1.0f), rotation.x, glm::vec3 (1, 0, 0));
	m = glm::rotate (m, rotation.y, glm::vec3 (0, 1, 0));
	m = glm::rotate (m, rotation.z, glm::vec3 (0, 0, 1));
	return m * glm::vec4 (0, 1, 0, 0);
}
glm::vec4 Camera::right () const {
	glm::mat4 m = glm::rotate (glm::mat4 (1.0f), rotation.x, glm::vec3 (1, 0, 0));
	m = glm::rotate (m, rotation.y, glm::vec3 (0, 1, 0));
	m = glm::rotate (m, rotation.z, glm::vec3 (0, 0, 1));
	return m * glm::vec4 (1, 0, 0, 0);
}