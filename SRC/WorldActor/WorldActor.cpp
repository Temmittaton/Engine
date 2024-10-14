#include "WorldActor.hpp"

// Constructors
WorldActor::WorldActor () {}

WorldActor::WorldActor (World& world) {
	core = Core ();

	world.AddWorldActor (this, core.position);
}
WorldActor::WorldActor (World& world, vec3 position) {
	core = Core (position, vec3 (0, 0, 0), vec3 (0, 0, 0));
}
WorldActor::WorldActor (World& world, Core icore) {
	core = icore;
}
WorldActor::WorldActor (World& world, WorldActor& iparent) {
	parent = &iparent;
	core = iparent.core;
	iparent.AddChild (this);
}

// Destructor
WorldActor::~WorldActor () {
	delete (id);
}

// Methods
WorldActor* WorldActor::GetParent () {
	return parent;
}

void WorldActor::AddChild (WorldActor* child) {

}

void WorldActor::Move (vec3 movement) {

}