#ifndef _WORLD_

#define _WORLD_

#include <vector>
#include <glm/glm.hpp>
#include "ID.h"
#include "Scene.h"
#include "../WorldActor/WorldActor.hpp"

class WorldActor;

class World {
public :
	// Attributes
	glm::vec3 worldDimensions, chunkNumber;
	unsigned int chunksDimensions, chunkLength;
	WorldActor* mainCamera;
	std::vector<std::vector<WorldActor*>> worldActors;
	glm::vec3 worldSkyColor;

	// Constructors
	World (glm::vec3 worldSize, unsigned int chunkSize, unsigned int chunkLength, glm::vec3 skyColor);

	// Methods
	struct Scene* GetSceneToRender () const;
	struct ID* AddWorldActor (WorldActor* instance, glm::vec3 pos);
};

#endif //_WORLD_