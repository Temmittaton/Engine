#ifndef _SCENE_

#define _SCENE_

#include "../WorldActor/WorldActor.hpp"

class WorldActor;

struct Scene {
	WorldActor** instances;

	Scene (unsigned int instanceNumber) {
		instances = new WorldActor * [instanceNumber];
	}

	~Scene () {
		delete [] instances;
	}
};

#endif //_SCENE_