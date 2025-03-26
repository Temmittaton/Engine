#include "World.h"

struct LightInfo {
	std::vector<float> *lights;
	vec3 skyColor;

	LightInfo (std::vector<float> *_lights, vec3 _skyColor) {
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

// Destructor
World::~World () {

}

// Methods
struct Scene* World::GetSceneToRender () const {
	unsigned int instanceNumber = 0; // need to add culling and optis soon this is terrible
	unsigned int linearSize = (worldDimensions.x * worldDimensions.y * worldDimensions.z) / (chunksDimensions * chunksDimensions * chunksDimensions);

	for (int i = 0; i < linearSize; i++) {
		for (int j = 0; j < (int)(chunkLength); j++) {
			if (worldActors [i][j] != NULL) {
				instanceNumber++;
			}
		}
	}

	Scene* _scene = new Scene (instanceNumber);
	instanceNumber = 0;
	_scene->camera = mainCamera;

	for (int i = 0; i < linearSize; i++) {
		for (int j = 0; j < (int)(chunkLength); j++) {
			if (worldActors [i][j] != NULL) {
				_scene->cores [instanceNumber] = ShaderCore (worldActors [i][j]->core.position, worldActors [i][j]->core.scale);
				_scene->materials [instanceNumber] = Material (worldActors [i][j]->model.color, worldActors [i][j]->model.lightIntensity);

				_scene->instances [instanceNumber] = Object (instanceNumber);
				instanceNumber++;
			}
		}
	}

	return _scene;
}

struct ID* World::AddWorldActor (WorldActor* instance, vec3 pos) {
	// Set instance to position (on sait jamais)
	instance->core.position = vec4 (pos.x, pos.y, pos.z, 0);

	// Transform pos to positive space
	vec3 pPos = (pos + worldDimensions) / vec3 (2);

	vec3 chunk = (pPos / vec3 (chunksDimensions));
	chunk.x = (int)chunk.x;
	chunk.y = (int)chunk.y;
	chunk.z = (int)chunk.z;
	int linearIndex = chunk[0] * chunkNumber[0] * chunkNumber [1] * chunkNumber [2] / chunksDimensions + chunk[1] * chunkNumber [1] * chunkNumber [2] / chunksDimensions + chunk [2] * chunkNumber [2] / chunksDimensions;

	int i = 0;
	while (i < worldActors[linearIndex].size ()) {
		if (worldActors [linearIndex][i] == NULL) {
			ID _id = ID (chunk, i, linearIndex);
			instance->id = &_id;

			worldActors [linearIndex][i] = instance;

			return &_id;
		}
		i++;
	}
	worldActors[linearIndex].push_back (instance);
	ID _id = ID (chunk, worldActors [linearIndex].size () - 1);
	instance->id = &_id;
	return &_id;
}