#include "Core.hpp"

#pragma once
class WorldActor {
public :
	// Attributes
	Core core;
	WorldActor* parent;
	WorldActor* children [8];

	// Constructors
	WorldActor ();
	WorldActor (Vector3 position);
	WorldActor (Core icore);
	WorldActor (WorldActor* iparent);

	// Methods
	void AddChild (WorldActor* child);
	WorldActor GetParent ();
	void Move (Vector3 movement);
};
