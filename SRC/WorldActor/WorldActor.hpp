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
	WorldActor ();
	WorldActor (Vector3 position);
	WorldActor (Core icore);
	WorldActor (WorldActor* iparent);

	// Methods
	void AddChild (WorldActor* child);
	WorldActor* GetParent ();
	void Move (Vector3 movement);

	static WorldActor CreateSphere (float radius = 1) {
		WorldActor sphere = WorldActor ();
		sphere.model = Model ();
		sphere.model.mesh = {true, radius};

		return sphere;
	}
};
