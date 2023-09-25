#include "World.h"
#include "../WorldActor/WorldActor.hpp"

// Constructors
World::World () {
	mainCamera = Camera ();
	worldActors [8];

	WorldActor sphere = WorldActor::CreateSphere ();
	worldActors [0] = &sphere;
}