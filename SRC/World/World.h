#ifndef _WORLD_

#define _WORLD_

#include <vector>
#include "../WorldActor/Camera.hpp"
#include "../WorldActor/WorldActor.hpp"

#pragma once

struct Scene {
	std::vector<Model*> models;
};

class World {
public :
	// Attributes
	vec3 worldDimensions, chunkNumber;
	unsigned int chunksDimensions, chunkLength;
	WorldActor* mainCamera;
	std::vector<std::vector<WorldActor*>> worldActors;
	vec3 worldSkyColor;

	// Constructors
	World (vec3 worldSize, unsigned int chunkSize, vec3 skyColor);

	// Methods
	struct Scene GetSceneToRender () const;
	struct ID AddWorldActor (WorldActor* instance, vec3 pos);
};

#endif _WORLD_