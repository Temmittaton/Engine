#include "WorldActor.hpp"
#include "../World/World.h"

// Constructors
WorldActor::WorldActor (World& world) {
	core = Core ();

	world.AddWorldActor (this, core.position);
}
WorldActor::WorldActor (World& world, Vector3 position) {
	core = Core (position, Vector3::zero, Vector3::zero);
}
WorldActor::WorldActor (World& world, Core icore) {
	core = icore;
}
WorldActor::WorldActor (World& world, WorldActor* iparent) {
	parent = iparent;
	core = iparent->core;
	iparent->AddChild (this);
}

// Methods
WorldActor* WorldActor::GetParent () {
	return parent;
}

void WorldActor::AddChild (WorldActor* child) {

}

void WorldActor::Move (Vector3 movement) {

}