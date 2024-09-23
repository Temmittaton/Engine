#ifndef _WORLDACTOR_

#define _WORLDACTOR_

#include "Core.hpp"
#include "Model.hpp"
#include "../World/World.h"
#include <glm/vec3.hpp>

#pragma once
class WorldActor {
public :
	// Attributes
	Core core;
	Model model;
	WorldActor* parent;
	WorldActor* children [8];

	// Constructors
	WorldActor ();
	WorldActor (World &world);
	WorldActor (World& world, vec3 position);
	WorldActor (World& world, Core icore);
	WorldActor (World& world, WorldActor* iparent);

	// Methods
	void AddChild (WorldActor* child);
	WorldActor* GetParent ();
	void Move (vec3 movement);
};

#endif _WORLDACTOR_