#ifndef _SCENE_

#define _SCENE_

#include "../WorldActor/Camera.hpp"
#include "../WorldActor/WorldActor.hpp"

class WorldActor;

struct Object {
	int cID, mID;

	Object (int ID = -1) {
		this->cID = ID;
		this->mID = ID;
	}
};
struct ShaderMaterial {
	vec3 color;
	float roughness;
	vec3 lightIntensity;
	float opaqueness;

	ShaderMaterial (vec3 col = vec3 (0,0,0), vec3 intensity = vec3 (0,0,0), float roughness = 1.0f, float opaqueness = 1.0f) {
		this->color = col;
		this->lightIntensity = intensity;
		this->roughness = roughness;
		this->opaqueness = opaqueness;
	}
};
struct ShaderCore {
	vec4 position, scale;

	ShaderCore (vec4 pos = vec4 (0,0,0,0), vec4 scale = vec4 (0,0,0,0)) {
		this->position = pos;
		this->scale = scale;
	}
};

struct Scene {
	unsigned int instanceNumber;
	ShaderCore* cores;
	ShaderMaterial* materials;
	Object* instances;
	Camera* camera;

	Scene (unsigned int instanceNumber) {
		this->instanceNumber = instanceNumber;
		instances = new Object [instanceNumber];
		cores = new ShaderCore [instanceNumber];
		materials = new ShaderMaterial [instanceNumber];

		camera = nullptr;
	}

	~Scene () {
		delete [] instances;
		delete [] cores;
		delete [] materials;
	}
};

#endif //_SCENE_