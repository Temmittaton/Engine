#include "Core.hpp"
#include "Model.hpp"

#pragma once
class WorldActor {
public :
	// Attributes
	Core core;
	Model model;
	WorldActor* parent;
	WorldActor* children [8];

	// Constructors
	WorldActor (World &world);
	WorldActor (World& world, Vector3 position);
	WorldActor (World& world, Core icore);
	WorldActor (World& world, WorldActor* iparent);

	// Methods
	void AddChild (WorldActor* child);
	WorldActor* GetParent ();
	void Move (Vector3 movement);

	static WorldActor CreateSphere (World& world, float radius = 1) {
		WorldActor sphere = WorldActor (world);
		sphere.model = Model ();
		sphere.model.mesh = {true, false, radius, Vector3 (1, 1, 1)};

		return sphere;
	}
};
