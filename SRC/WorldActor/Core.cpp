#include "Core.hpp"

// Constructors
Core::Core () {
	position = glm::vec3 (0, 0, 0);
	scale = glm::vec3 (1, 1, 1);
	rotation = glm::vec3 (0, 0, 0);
}
Core::Core (glm::vec3 ipos, glm::vec3 iscale = glm::vec3 (1, 1, 1), glm::quat irot = glm::quat (1, 0, 0, 0)) {
	position = ipos;
	scale = iscale;
	rotation = irot;
}

// Methods
glm::vec3 Core::forward () const {
	return glm::rotate (glm::inverse (rotation), glm::vec3 (0.0, 0.0, 1.0));
}
glm::vec3 Core::up () const {
	return glm::rotate (glm::inverse (rotation), glm::vec3 (0.0, 1.0, 0.0));
}
glm::vec3 Core::right () const {
	return glm::rotate (glm::inverse (rotation), glm::vec3 (1.0, 0.0, 0.0));
}
