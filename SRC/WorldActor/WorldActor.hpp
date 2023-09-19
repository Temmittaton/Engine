#include "Core.hpp"

#pragma once
class WorldActor {
public :
	Core core;

	// Constructors
	WorldActor ();
	WorldActor (Vector3 position);
	WorldActor (Core icore);
};
