#include <vector>
#include "../WorldActor/Camera.hpp"
#include "../WorldActor/WorldActor.hpp"

#pragma once
class World {
public :
	// Attributes
	Vector3 worldDimensions, chunkNumber;
	unsigned int chunksDimensions, chunkLength;
	WorldActor* mainCamera;
	std::vector<std::vector<WorldActor*>> worldActors;
	Vector3 worldSkyColor;

	// Constructors
	World (Vector3 worldSize, unsigned int chunkSize, Vector3 skyColor);

	// Methods
	Mesh* GetSceneActors () const;
	struct LightInfo GetLights ();
	struct ID AddWorldActor (WorldActor* instance, Vector3 pos);
};
