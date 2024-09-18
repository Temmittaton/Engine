#include "World.h"
#include "../WorldActor/WorldActor.hpp"

struct ID {
	Vector3 ChunkID;
	unsigned int nID;

	ID (Vector3 _chunkID, unsigned int _ID) {
		ChunkID = _chunkID;
		nID = _ID;
	}
};
struct LightInfo {
	std::vector<Light*> *lights;
	Vector3 skyColor;

	LightInfo (std::vector<Light*> *_lights, Vector3 _skyColor) {
		lights = _lights;
		skyColor = _skyColor;
	}
};

// Constructors
World::World (Vector3 worldSize, unsigned int chunkSize, Vector3 skyColor) {
	// Setting up worldActors array, chunks
	worldDimensions = worldSize;
	chunksDimensions = chunkSize;

	chunkNumber = (worldSize / chunksDimensions).toInt3 ();
	worldActors = std::vector<std::vector<WorldActor*>> (chunkNumber[0] * chunkNumber [1] * chunkNumber [2], std::vector<WorldActor*> (16));

	worldSkyColor = skyColor;

	// Instance camera
	mainCamera = new Camera (*this);


	(*mainCamera).core.position = Vector3 (0, 0, -5);

	WorldActor sphere = WorldActor::CreateSphere (*this);
}

Mesh* World::GetSceneActors () const {
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

struct LightInfo World::GetLights () {
	std::vector<Light*> lights;
	for (int i = 0; i < worldActors.size (); i++) {
		for (int j = 0; j < worldActors [i].size (); j++) {
			if (&worldActors [i][j]->model.light != NULL) {
				lights.push_back (&worldActors[i][j]->model.light);
			}
		}
	}

	return LightInfo (&lights, worldSkyColor);
}

struct ID World::AddWorldActor (WorldActor* instance, Vector3 pos) {
	// Transform pos to positive space
	Vector3 pPos = (pos + worldDimensions) / 2;

	Vector3 chunk = (pPos / chunksDimensions).toInt3 ();
	int linearIndex = chunk[0] * chunkNumber[0] * chunkNumber [1] * chunkNumber [2] + chunk[1] * chunkNumber [1] * chunkNumber [2] + chunk [2] * chunkNumber [2];

	int i = 0;
	while (i < worldActors[linearIndex].size ()) {
		if (worldActors [linearIndex][i] == NULL) {
			return ID (chunk, i);
		}
	}
	worldActors[linearIndex].push_back (instance);
	return ID (chunk, worldActors[linearIndex].size () - 1);
}