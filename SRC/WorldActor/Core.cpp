#include "Core.hpp"

// Constructors
Core::Core () {
	position = glm::vec4 (0, 0, 0, 0);
	scale = glm::vec4 (1, 1, 1, 1);
}
Core::Core (glm::vec4 ipos, glm::vec4 iscale = glm::vec4 (1, 1, 1, 0)) {
	position = ipos;
	scale = iscale;
}

glm::vec3 Core::forward () const {
	return glm::vec3 (0,0,1);
}
glm::vec3 Core::up () const {
	return glm::vec3 (0, 1, 0);
}
glm::vec3 Core::right () const {
	return glm::vec3 (1, 0, 0);
}