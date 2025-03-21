#ifndef _SCENE_

#define _SCENE_

#include "../WorldActor/Camera.hpp"
#include "../WorldActor/WorldActor.hpp"

class WorldActor;

struct Object {
	int coreIndex, meshIndex;

	Object (int coreID = -1, int meshID = -1) {
		this->coreIndex = coreID;
		this->meshIndex = meshID;
	}
};
struct ShaderCam {
	vec3 pos;
	vec3 forward;
	vec4 values;

	ShaderCam (Camera &camera) {
		this->pos = camera.core.position;
		this->forward = camera.core.forward ();
		this->values = camera.values;
	}
};

struct Scene {
	unsigned int instanceNumber;
	unsigned int meshNumber;
	unsigned int lightNumber;
	Core* cores;
	Mesh* meshes;
	Material* materials;
	Object* instances;
	unsigned int* lightIndexes; // two by two, first is linear index and second is index in chunk
	ShaderCam* camera;

	Scene (unsigned int instanceNumber, unsigned int meshNumber, unsigned int lightNumber, Camera &sceneCamera) {
		this->instanceNumber = instanceNumber;
		this->meshNumber = meshNumber;
		this->lightNumber = lightNumber;
		instances = new Object [instanceNumber];
		cores = new Core [instanceNumber];
		meshes = new Mesh [meshNumber];
		materials = new Material [meshNumber];

		lightIndexes = new unsigned int [lightNumber * 2];

		camera = new ShaderCam (sceneCamera);
	}

	~Scene () {
		delete [] instances;
		delete [] cores;
		delete [] meshes;
		delete [] materials;
		delete [] lightIndexes;
		delete camera;
	}
};

#endif //_SCENE_