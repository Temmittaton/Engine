#include "WorldActor.hpp"

// Constructors
WorldActor::WorldActor () {
	core = Core ();
}
WorldActor::WorldActor (Vector3 position) {
	core = Core (position, Vector3::zero, Vector3::zero);
}
WorldActor::WorldActor (Core icore) {
	core = icore;
}
