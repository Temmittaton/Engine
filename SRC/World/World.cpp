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

	linearSize = (worldDimensions.x * worldDimensions.y * worldDimensions.z) / (chunksDimensions * chunksDimensions * chunksDimensions);

	worldActors = std::vector<std::vector<WorldActor*>> (chunkNumber[0] * chunkNumber [1] * chunkNumber [2], std::vector<WorldActor*> (chunkLength));

	worldSkyColor = skyColor;

	mainCamera = nullptr;

	instanceNumber = 0;
}

// Destructor
World::~World () {

}

// Methods
struct Scene* World::GetSceneToRender () const {
	unsigned int instancesToRender = instanceNumber; // need to add culling and optis soon this is terrible
	unsigned int n = 0;

	/*for (int i = 0; i < linearSize; i++) {
		for (int j = 0; j < (int)(chunkLength); j++) {
			if (worldActors [i][j] != NULL) {
				instancesToRender++;
			}
		}
	}*/

	Scene* _scene = new Scene (instancesToRender);
	instancesToRender = 0;
	_scene->camera = mainCamera;

	for (int i = 0; i < linearSize; i++) {
		for (int j = 0; j < (int)(chunkLength); j++) {
			if (n > instanceNumber) { break; };
			if (worldActors [i][j] == NULL) {continue;}

			_scene->cores [instancesToRender] = ShaderCore (worldActors [i][j]->core.position, worldActors [i][j]->core.scale);
			_scene->materials [instancesToRender] = ShaderMaterial (worldActors [i][j]->model.color, worldActors [i][j]->model.lightIntensity, worldActors [i][j]->model.roughness, worldActors [i][j]->model.opaqueness);

			_scene->instances [instancesToRender] = Object (instancesToRender);
			instancesToRender++;
			n++; // end search if searched every instance
		}
	}

	return _scene;
}

struct ID* World::AddWorldActor (WorldActor* instance) {
	instanceNumber++;

	// Transform pos to positive space
	vec3 pos = instance->core.position;
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

float World::GetCollision (ID id, vec3 move) {
	float t = -1.0f;
	unsigned int n = 0;

	vec3 p1 = worldActors [id.linearID][id.nID]->core.position;
	float r1 = worldActors [id.linearID][id.nID]->core.scale.x;
	float a = move.x * move.x + move.y * move.y + move.z * move.z;

	for (int i = 0; i < linearSize; i++) {
		for (int j = 0; j < (int)(chunkLength); j++) {
			if (n > instanceNumber) { break; };
			if (worldActors [i][j] == NULL) { continue; }
			n++; // end search if searched every instance

			vec3 p2 = worldActors [i][j]->core.position;
			float r = r1 + worldActors [i][j]->core.scale.x;
				
			float halfB = (p1.x - p2.x) * move.x + (p1.y - p2.y) * move.y + (p1.z - p2.z) * move.z;
			float c = p1.x * p1.x + p2.x * p2.x + p1.y * p1.y + p2.y * p2.y + p1.z * p1.z + p2.z * p2.z - 2 * (p1.x*p2.x+p1.y*p2.y+p1.z*p2.z) - r * r;
			float deltaFourth = halfB * halfB - a * c;

			// If no collision, return -1.
			if (deltaFourth < 0.0f) {
				t = max (t, -1.0f);
				continue;
			}

			float t1 = (-2 * halfB - sqrt (4 * deltaFourth)) / (2 * a);
			float t2 = (-2 * halfB + sqrt (4 * deltaFourth)) / (2 * a);

			if (t1 >= 0.0f && t1 < 1.0f) {
				if (t2 >= 0.0f && t2 < 1.0f) {
					t = min (t, min (t1, t2));
				}
				else {
					t = min (t, t1);
				}
			}
			else if (t2 >= 0.0f && t2 < 1.0f) {
				t = min (t, t2);
			}
			else {
				t = max (t, -1.0f);
			}
		}
	}

	return t;
}
