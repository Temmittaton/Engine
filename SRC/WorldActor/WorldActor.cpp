#include "WorldActor.hpp"

class WorldActor {
public :
	Core core;

	// Constructors
	WorldActor () {
		core = Core ();
	}
	WorldActor (Vector3 position) {
		core = Core (position, Vector3::zero, Vector3::zero);
	}
	WorldActor (Core icore) {
		core = icore;
	}
};
