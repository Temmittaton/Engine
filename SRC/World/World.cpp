#include "World.h"
#include "../WorldActor/WorldActor.hpp"

// Constructors
World::World () {
	mainCamera = (WorldActor)Camera ();
	mainCamera.core.position = Vector3 (0, 0, -5);
	worldActors [8];

	WorldActor sphere = WorldActor::CreateSphere ();
	worldActors [0] = &sphere;
}
