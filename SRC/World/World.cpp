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

Mesh* World::GetSceneActors () {
	unsigned int n = 0;
	while (worldActors [n] != NULL) {
		n++;
	}

	Mesh* meshes = new Mesh [n];
	for (int i = 0; i < n; i++) {
		meshes [i] = worldActors [i]->model.mesh;
	}

	return meshes;
}

Light* World::GetLights () {
	unsigned int n = 0;
	while (worldActors [n] != NULL) {
		if (&worldActors [n]->model.light != nullptr) {
			n++;
		}
	}

	Light* lights = new Light [n];
	for (int i = 0; i < n; i++) {
		lights [i] = worldActors [i]->model.light;
	}

	return lights;
}
