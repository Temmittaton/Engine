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
WorldActor::WorldActor (WorldActor* iparent) {
	parent = iparent;
	core = iparent->core;
}

// Methods
WorldActor* WorldActor::GetParent () {
	return parent;
}
void WorldActor::AddChild (WorldActor* child) {

}

void WorldActor::Move (Vector3 movement) {

}