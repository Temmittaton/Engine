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
struct Material {
	vec4 color, lightIntensity;

	Material (vec4 col = vec4 (0,0,0,0), vec4 intensity = vec4 (0,0,0,0)) {
		this->color = col;
		this->lightIntensity = intensity;
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
	Material* materials;
	Object* instances;
	Camera* camera;

	Scene (unsigned int instanceNumber) {
		this->instanceNumber = instanceNumber;
		instances = new Object [instanceNumber];
		cores = new ShaderCore [instanceNumber];
		materials = new Material [instanceNumber];
	}

	~Scene () {
		delete [] instances;
		delete [] cores;
		delete [] materials;
	}
};

#endif //_SCENE_