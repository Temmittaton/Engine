#include "../WorldActor/Camera.hpp"
#include "../WorldActor/WorldActor.hpp"

#pragma once
class World {
public :
	// Attributes
	Vector3 worldDimensions;
	unsigned int chunksDimensions, chunkLength;
	WorldActor* mainCamera;
	WorldActor* worldActors [];

	// Constructors
	World (Vector3 worldSize, unsigned int chunkSize, unsigned int averageDensity);

	// Methods
	Mesh* GetSceneActors () const;
	Light* GetLights ();
};
