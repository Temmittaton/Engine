#include "World.h"

struct LightInfo {
	std::vector<Light*> *lights;
	vec3 skyColor;

	LightInfo (std::vector<Light*> *_lights, vec3 _skyColor) {
		lights = _lights;
		skyColor = _skyColor;
	}
};

// Constructors
World::World (vec3 worldSize, unsigned int chunkSize, unsigned int chunkLength, vec3 skyColor) {
	// Setting up worldActors array, chunks
	worldDimensions = worldSize;
	chunksDimensions = chunkSize;

	this->chunkLength = chunkLength;
	chunkNumber = (worldSize / vec3(chunksDimensions));

	chunkNumber.x = (int)chunkNumber.x;
	chunkNumber.y = (int)chunkNumber.y;
	chunkNumber.z = (int)chunkNumber.z;

	worldActors = std::vector<std::vector<WorldActor*>> (chunkNumber[0] * chunkNumber [1] * chunkNumber [2], std::vector<WorldActor*> (chunkLength));

	worldSkyColor = skyColor;
}

struct Scene* World::GetSceneToRender () const {
	unsigned int instanceNumber = 0; // need to add culling and optis soon this is terrible
	unsigned int lightNumber = 0;
	unsigned int linearSize = (worldDimensions.x * worldDimensions.y * worldDimensions.z) / (chunksDimensions * chunksDimensions * chunksDimensions);

	for (int i = 0; i < linearSize; i++) {
		for (int j = 0; j < (int)(chunkLength); j++) {
			if (worldActors [i][j] != NULL) {
				instanceNumber++;

				if (worldActors [i][j]->model.mesh.material.isLight) {
					lightNumber++;
				}
			}
		}
	}

	Scene* _scene = new Scene (instanceNumber, lightNumber);
	instanceNumber = 0;
	lightNumber = 0;

	for (int i = 0; i < linearSize; i++) {
		for (int j = 0; j < (int)(chunkLength); j++) {
			if (worldActors [i][j] != NULL) {
				_scene->instances [instanceNumber] = Object (worldActors [i][j]->core, worldActors [i][j]->model);
				instanceNumber++;

				if (worldActors [i][j]->model.mesh.material.isLight) {
					_scene->lightIndexes [lightNumber] = i;
					_scene->lightIndexes [lightNumber + 1] = j;
					lightNumber += 2;
				}
			}
		}
	}

	return _scene;
}

struct ID* World::AddWorldActor (WorldActor* instance, vec3 pos) {
	// Transform pos to positive space
	vec3 pPos = (pos + worldDimensions) / vec3 (2);

	vec3 chunk = (pPos / vec3 (chunksDimensions));
	int linearIndex = chunk[0] * chunkNumber[0] * chunkNumber [1] * chunkNumber [2] + chunk[1] * chunkNumber [1] * chunkNumber [2] + chunk [2] * chunkNumber [2];

	int i = 0;
	while (i < worldActors[linearIndex].size ()) {
		if (worldActors [linearIndex][i] == NULL) {
			ID _id = ID (chunk, i);
			instance->id = &_id;
			return &_id;
		}
	}
	worldActors[linearIndex].push_back (instance);
	ID _id = ID (chunk, worldActors [linearIndex].size () - 1);
	instance->id = &_id;
	return &_id;
}