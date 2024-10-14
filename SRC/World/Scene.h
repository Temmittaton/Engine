#ifndef _SCENE_

#define _SCENE_

#include "../WorldActor/WorldActor.hpp"

class WorldActor;

struct Object {
	Core core;
	Model model;

	Object (Core core = Core (), Model model = Model ()) {
		this->core = core;
		this->model = model;
	}
};

struct Scene {
	Object* instances;
	unsigned int* lightIndexes; // two by two, first is linear index and second is index in chunk

	Scene (unsigned int instanceNumber, unsigned int lightNumber) {
		instances = new Object [instanceNumber];
		lightIndexes = new unsigned int [lightNumber];
	}

	~Scene () {
		delete [] instances;
		delete [] lightIndexes;
	}
};

#endif //_SCENE_