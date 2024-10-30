#ifndef _SCENE_

#define _SCENE_

#include "../WorldActor/WorldActor.hpp"

class WorldActor;

struct Object {
	int coreIndex, meshIndex;

	Object (int coreID = -1, int meshID = -1) {
		this->coreIndex = coreID;
		this->meshIndex = meshID;
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

	Scene (unsigned int instanceNumber, unsigned int meshNumber, unsigned int lightNumber) {
		this->instanceNumber = instanceNumber;
		this->meshNumber = meshNumber;
		this->lightNumber = lightNumber;
		instances = new Object [instanceNumber];
		cores = new Core [instanceNumber];
		meshes = new Mesh [meshNumber];
		materials = new Material [meshNumber];

		lightIndexes = new unsigned int [lightNumber * 2];
	}

	~Scene () {
		delete [] instances;
		delete [] cores;
		delete [] meshes;
		delete [] materials;
		delete [] lightIndexes;
	}
};

#endif //_SCENE_