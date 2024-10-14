#ifndef _CORE_

#define _CORE_

#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

class Core {
public:
	glm::vec3 position, scale;
	glm::quat rotation;

	// Constructors
	Core ();
	Core (glm::vec3 ipos, glm::vec3 iscale, glm::quat irot);

	glm::vec3 forward () const;
	glm::vec3 up () const;
	glm::vec3 right () const;
};

#endif //_CORE_