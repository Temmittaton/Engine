#include "World.h"

struct ID {
	vec3 ChunkID;
	unsigned int nID;

	ID (vec3 _chunkID, unsigned int _ID) {
		ChunkID = _chunkID;
		nID = _ID;
	}
};
struct LightInfo {
	std::vector<Light*> *lights;
	vec3 skyColor;

	LightInfo (std::vector<Light*> *_lights, vec3 _skyColor) {
		lights = _lights;
		skyColor = _skyColor;
	}
};

// Constructors
World::World (vec3 worldSize, unsigned int chunkSize, vec3 skyColor) {
	// Setting up worldActors array, chunks
	worldDimensions = worldSize;
	chunksDimensions = chunkSize;

	chunkNumber = (worldSize / vec3(chunksDimensions));

	chunkNumber.x = (int)chunkNumber.x;
	chunkNumber.y = (int)chunkNumber.y;
	chunkNumber.z = (int)chunkNumber.z;

	worldActors = std::vector<std::vector<WorldActor*>> (chunkNumber[0] * chunkNumber [1] * chunkNumber [2], std::vector<WorldActor*> (16));

	worldSkyColor = skyColor;

	// Instance camera
	mainCamera = new Camera ();


	(*mainCamera).core.position = vec3 (0, 0, -5);
}

struct Scene World::GetSceneToRender () const {
	return Scene ();
}

struct ID World::AddWorldActor (WorldActor* instance, vec3 pos) {
	// Transform pos to positive space
	vec3 pPos = (pos + worldDimensions) / vec3 (2);

	vec3 chunk = (pPos / vec3 (chunksDimensions));
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