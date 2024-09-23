#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#ifndef CORE_H
#define CORE_H

class Core {
public:
	glm::vec3 position, scale;
	glm::quat rotation;

	// Constructors
	Core ();
	Core (glm::vec3 ipos, glm::vec3 iscale = glm::vec3 (1, 1, 1), glm::quat irot = glm::quat (0, 1, 0, 0));

	glm::vec3 forward () const;
	glm::vec3 up () const;
	glm::vec3 right () const;
};

#endif