#include "../WorldActor/Camera.hpp"
#include "../WorldActor/WorldActor.hpp"

#pragma once
class World {
public :
	// Attributes
	WorldActor mainCamera;
	WorldActor* worldActors [];

	// Constructors
	World ();

	// Methods
	Mesh* GetSceneActors ();
	Light* GetLights ();
};
