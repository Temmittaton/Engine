#include "WorldActor.hpp"

// Constructors
WorldActor::WorldActor () {
	world = nullptr;
	core = Core ();
	parent = nullptr;
}

WorldActor::WorldActor (World* world) {
	this->world = world;
	core = Core ();
	parent = nullptr;
}
WorldActor::WorldActor (World* world, vec4 position) {
	this->world = world;
	core = Core (position, vec4 (1, 1, 1, 0));
}
WorldActor::WorldActor (World* world, Core icore) {
	this->world = world;
	core = icore;
}
WorldActor::WorldActor (World* world, WorldActor& iparent) {
	this->world = world;
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

bool WorldActor::Move (vec3 movement) {
	float t = world->GetCollision (*id, movement);

	if (t < 0.5f) {
		core.position += vec4 (movement, 0); // No collision : full movement
		return true;
	}
	else {
		core.position += vec4 (movement, 0) * t; // Collision : partial movement
		return false;
	}
}