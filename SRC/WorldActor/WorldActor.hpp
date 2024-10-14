#ifndef _WORLDACTOR_

#define _WORLDACTOR_
#include <glm/vec3.hpp>

#include "Core.hpp"
#include "Model.hpp"
#include "../World/World.h"
#include "../World/ID.h"

class World;
struct ID;

class WorldActor {
public :
	// Attributes
	Core core;
	Model model;
	WorldActor* parent;
	WorldActor* children [8];
	ID* id = new ID (glm::vec3 (0), 0);

	// Constructors
	WorldActor ();
	WorldActor (World& world);
	WorldActor (World& world, vec3 position);
	WorldActor (World& world, Core icore);
	WorldActor (World& world, WorldActor& iparent);

	// Destructor
	~WorldActor ();

	// Methods
	void AddChild (WorldActor* child);
	WorldActor* GetParent ();
	void Move (vec3 movement);
};

#endif //_WORLDACTOR_