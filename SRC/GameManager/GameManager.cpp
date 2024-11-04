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

	WorldActor* debugWA = new WorldActor ();

	vec4 _vertices [3] = {vec4 (0, 1, 0, 0), vec4 (-1, -1, 0, 0), vec4 (1, -1, 0, 0)};
	unsigned int _indices [3] = {1, 2, 3};

	debugWA->model.mesh = Mesh (_vertices, _indices, Material (vec4 (.6, .1, .3, 1), Light (vec4 (.5), vec4 (1, 0, 1, 1))));
	currentWorld->AddWorldActor (debugWA, vec3 (0, 0, 0));
}

void GameManager::Frame () {
	gameTime += .1;
}
