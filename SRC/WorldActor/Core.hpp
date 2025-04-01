#ifndef _CORE_

#define _CORE_

#include "glm.hpp"

class Core {
public:
	glm::vec4 position; // The sphere's position in the world
	glm::vec4 scale; // x is the sphere's radius, the others are unused for now

	// Constructors
	Core ();
	Core (glm::vec4 ipos, glm::vec4 iscale);

	// Methods
	glm::vec3 forward () const;
	glm::vec3 up () const;
	glm::vec3 right () const;
};

#endif //_CORE_