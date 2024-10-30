#include "GameManager.hpp"
#include "../WorldActor/Camera.hpp"

// Constructor
GameManager::GameManager () {
	currentWorld = new World (glm::vec3 (64), 16, 16, glm::vec3 (0.6, 0.4, 1));
	gameTime = 0.0;
}

// Destructor
GameManager::~GameManager () {
	delete currentWorld;
}

// Methods
void GameManager::Init () {
	/*WorldActor* debugActor = new WorldActor ();
	currentWorld->AddWorldActor (debugActor, vec3 (0, 0, 5));

	WorldActor* debugCamera = new Camera ();
	currentWorld->AddWorldActor (debugCamera, vec3 (0, 0, 0));*/

	WorldActor* debugLight = new WorldActor ();
	debugLight->model.mesh.material = Material (vec3 (.6, 0, 0), true, Light (1, vec3 (1, 0, 0)));
	currentWorld->AddWorldActor (debugLight, vec3 (-2, 3, 0));
}

void GameManager::Frame () {
	gameTime += .1;
}
