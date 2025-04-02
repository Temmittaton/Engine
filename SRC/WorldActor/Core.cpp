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